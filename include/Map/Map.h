#ifndef _MAP_H_
#define _MAP_H_

#include <Simulation/SimulationStatus.h>

#include <stdio.h>

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class MovingBody;

class Map: public SimulationStatus
{
	static const int constexpr npts = 21600;
	static const double constexpr cellsize = 0.004166666667;
	
	std::string directory;
	
	struct st_datafile
	{
		const std::string filename;
		double xllcorner;
		double yllcorner;
		FILE *f;
	};
	
	std::vector<st_datafile> datafiles;
	
	int get_datafile_index(double lat, double lng) const;
	long get_datafile_offset(int datafile_idx, double lat, double lng) const;
	
	const MovingBody *moving_body;
	
public:
	Map(const MovingBody *moving_body);
	~Map();
	
	std::string GetName() const { return "map"; }
	
	short GetDepth(double lat, double lng) const;
	
	nlohmann::json ToJson() const;
	
	static bool EsriToBinary(const std::string &in, const std::string out);
};

#endif
