#ifndef _SIMULATIONSTATUS_H_
#define _SIMULATIONSTATUS_H_

#include <vector>
#include <thread>
#include <mutex>
#include <string>

#include <nlohmann/json.hpp>

class SimulationStatus
{
	struct obj_thread
	{
		SimulationStatus *obj;
		std::thread::id thread_id;
	};
	
	
	static std::vector<obj_thread> simulation_objs;
	static std::mutex g_mutex;
	
protected:
	double last_update = 0;
	double update_resolution = 0.1;
	
public:
	SimulationStatus();
	virtual ~SimulationStatus();
	
	virtual std::string GetName() const = 0;
	
	virtual nlohmann::json ToJson() const = 0;
	
	static nlohmann::json GetStatus(double t);
	void Invalidate();
};

#endif
