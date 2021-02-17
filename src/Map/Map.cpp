#include <Map/Map.h>
#include <Dynamic/MovingBody.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

using json = nlohmann::json;

Map::Map(const MovingBody *moving_body)
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
