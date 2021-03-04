#include <Map/Map.h>
#include <Dynamic/MovingBody.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

using json = nlohmann::json;

Map::Map(MovingBody *moving_body)
{
	directory = "/home/bob/fonds/data";
	
	// North emisphere
	datafiles.push_back({"gebco_2020_n90.0_s0.0_w-180.0_e-90.0.asc.bin", -180, 0, 0});
	datafiles.push_back({"gebco_2020_n90.0_s0.0_w-90.0_e0.0.asc.bin", -90, 0, 0});
	datafiles.push_back({"gebco_2020_n90.0_s0.0_w0.0_e90.0.asc.bin", 0, 0, 0});
	datafiles.push_back({"gebco_2020_n90.0_s0.0_w90.0_e180.0.asc.bin", 90, 0, 0});
	
	// South emisphere
	datafiles.push_back({"gebco_2020_n0.0_s-90.0_w-180.0_e-90.0.asc.bin", -180, -90, 0});
	datafiles.push_back({"gebco_2020_n0.0_s-90.0_w-90.0_e0.0.asc.bin", -90, -90, 0});
	datafiles.push_back({"gebco_2020_n0.0_s-90.0_w0.0_e90.0.asc.bin", 0, -90, 0});
	datafiles.push_back({"gebco_2020_n0.0_s-90.0_w90.0_e180.0.asc.bin", 90, -90, 0});
	
	for(auto it=datafiles.begin();it!=datafiles.end();++it)
	{
		string path = directory+"/"+it->filename;
		it->f = fopen(path.c_str(), "r");
	}
	
	this->moving_body = moving_body;
	update_resolution = 1;
	
	double a = 6378137, f = 1/298.257223563; /* WGS84 */ 
	geod_init(&geod, a, f);
}

Map::~Map()
{
	for(auto it=datafiles.begin();it!=datafiles.end();++it)
		fclose(it->f);
}

int Map::get_datafile_index(double lat, double lng) const
{
	int idx = 0;
	if(lat<0)
		idx += 4;
	
	idx += (((int)lng)+180)/90;
	
	return idx;
}

long Map::get_datafile_offset(int datafile_idx, double lat, double lng) const
{
	long y = (int)((datafiles[datafile_idx].yllcorner + (double)npts * cellsize - lat) / cellsize) * npts * sizeof(short);
	long x = (int)((lng-datafiles[datafile_idx].xllcorner) / cellsize) * sizeof(short);
	
	return y+x;
}

bool Map::get_cell_out(int cell_lat, int cell_lng, double lat, double lng, double heading, double *out_lat, double *out_lng, int *out_dir) const
{
	double bottom = cell_lat*cellsize;
	double top = (cell_lat+1)*cellsize;
	double left = cell_lng*cellsize;
	double right = (cell_lng+1)*cellsize;
	
	if(heading==0)
	{
		*out_lat = top;
		*out_lng = lng;
		*out_dir = 1;
		return true;
	}
	
	if(heading==M_PI || heading==-M_PI)
	{
		*out_lat = bottom;
		*out_lng = lng;
		*out_dir = 3;
		return true;
	}
	
	double a = M_PI/2-heading;
	double m = tan(a);
	double p = lat - tan(a)*lng;
	
	if(m==0)
	{
		if(heading>0)
		{
			*out_lat = lat;
			*out_lng = right;
			*out_dir = 2;
			return true;
		}
		else
		{
			*out_lat = lat;
			*out_lng = left;
			*out_dir = 4;
			return true;
		}
	}
	
	double lat_top = top;
	double lng_top = (top - p) / m;
	if(a>=0 && a<=M_PI && lng_top>=left && lng_top<=right)
	{
		*out_lat = lat_top;
		*out_lng = lng_top;
		*out_dir = 1;
		return true;
	}
	
	double lat_bottom = bottom;
	double lng_bottom = (bottom - p) / m;
	if((a<0 || a>M_PI) && lng_bottom>=left && lng_bottom<=right)
	{
		*out_lat = lat_bottom;
		*out_lng = lng_bottom;
		*out_dir = 3;
		return true;
	}
	
	double lat_left = m * left + p;
	double lng_left = left;
	if((a<-M_PI/2  || a>M_PI/2) && lat_left>=bottom && lat_left<=top)
	{
		*out_lat = lat_left;
		*out_lng = lng_left;
		*out_dir = 4;
		return true;
	}
	
	double lat_right = m * right + p;
	double lng_right = right;
	if(a>=-M_PI/2 && a<=M_PI/2 && lat_right>=bottom && lat_right<=top)
	{
		*out_lat = lat_right;
		*out_lng = lng_right;
		*out_dir = 2;
		return true;
	}
	
	return false;
}

double Map::GetCollisionDistance(double lat, double lng, double heading) const
{
	double dst;
	double cur_lat = lat, cur_lng = lng;
	double out_lat, out_lng;
	int out_dir;
	int cell_bottom = lat>0?(int)(lat/cellsize):(int)(lat/cellsize)-1;
	int cell_left = lng>0?(int)(lng/cellsize):(int)(lng/cellsize)-1;
	
	Vector3D position = moving_body->GetPosition();
	
	for(int i=0;i<20;i++)
	{
		short depth = GetDepth(cell_bottom*cellsize+cellsize/2, cell_left*cellsize+cellsize/2);
		if(depth>position.z)
		{
			geod_inverse(&geod, lat, lng, cur_lat, cur_lng, &dst, 0, 0);
			return dst;
		}
		
		if(!get_cell_out(cell_bottom, cell_left, cur_lat, cur_lng, heading, &out_lat, &out_lng, &out_dir))
			return -1;
		
		if(out_dir==1)
			cell_bottom++;
		else if(out_dir==2)
			cell_left++;
		else if(out_dir==3)
			cell_bottom--;
		else if(out_dir==4)
			cell_left--;
		
		cur_lat = out_lat;
		cur_lng = out_lng;
	}
	
	return -1;
}

short Map::GetDepth(double lat, double lng) const
{
	int idx = get_datafile_index(lat, lng);
	long offset = get_datafile_offset(idx, lat, lng);
	
	fseek(datafiles[idx].f, offset, SEEK_SET);
	
	short depth;
	fread(&depth, 1, sizeof(short), datafiles[idx].f);
	
	return depth;
}

void Map::HandleCommand(const nlohmann::json &j)
{
	if(j["action"]=="scale_plus")
	{
		scale -= 0.005;
		if(scale<0.01)
			scale = 0.01;
	}
	else if(j["action"]=="scale_minus")
	{
		scale += 0.005;
		if(scale>0.1)
			scale = 0.1;
	}
	else if(j["action"]=="jumpto")
	{
		moving_body->JumpTo(stod((string)j["latitude"]), stod((string)j["longitude"]));
	}
	
	Invalidate();
}

json Map::ToJson() const
{
	double latitude, longitude;
	moving_body->GetLatLng(&latitude, &longitude);
	
	double from_lat = latitude+scale;
	double from_lng = longitude-scale;
	double to_lat = latitude-scale;
	double to_lng = longitude+scale;
	
	int xpts = abs((to_lng - from_lng)/cellsize);
	int ypts = abs((to_lat - from_lat)/cellsize);
	
	double xstep = (to_lng>=from_lng)?cellsize:-cellsize;
	double ystep = (to_lat>=from_lat)?cellsize:-cellsize;
	
	json rows;
	for(int y = 0; y <= ypts; y++)
	{
		json row;
		for(int x = 0; x <= xpts; x++)
			row[x] = GetDepth(from_lat + y * ystep, from_lng + x * xstep);
		rows[y] = row;
	}
	
	Vector3D attitude = moving_body->GetAttitude();
	
	json j;
	j["depthmap"] = rows;
	j["depth"] = GetDepth(latitude, longitude);
	j["orientation"] = attitude.z/M_PI*180;
	
	j["gps"]["latitude"] = latitude;
	j["gps"]["longitude"] = longitude;
	
	j["collision_front"] = GetCollisionDistance(latitude, longitude, attitude.z);
	
	return j;
}

bool Map::EsriToBinary(const string &in, const string out)
{
	char buf[npts * 16];
	
	FILE *fin = fopen(in.c_str(), "r");
	if(!fin)
		return false;
	
	FILE *fout = fopen(out.c_str(), "w");
	if(!fout)
	{
		fclose(fin);
		return false;
	}
	
	fgets(buf, npts * 16, fin);
	fgets(buf, npts * 16, fin);
	fgets(buf, npts * 16, fin);
	fgets(buf, npts * 16, fin);
	fgets(buf, npts * 16, fin);
	fgets(buf, npts * 16, fin);
	
	while(fgets(buf, npts * 16, fin))
	{
		char *ptr = strtok(buf, " ");
		while(ptr)
		{
			short depth = atoi(ptr);
			if(depth>10000)
				printf("%d\n",depth);
			fwrite(&depth, 1, sizeof(depth), fout);
			ptr = strtok(0, " ");
		}
	}
	
	
	fclose(fin);
	fclose(fout);
	
	return true;
}
