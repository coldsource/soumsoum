#ifndef _SIMULATIONOBJECT_H_
#define _SIMULATIONOBJECT_H_

#include <vector>
#include <thread>
#include <mutex>

class SimulationObject
{
	struct obj_thread
	{
		SimulationObject *obj;
		std::thread::id thread_id;
	};
	
	
	static std::vector<obj_thread> simulation_objs;
	static std::mutex g_mutex;
	
protected:
	void variable_sim(double *current, double target, double rate, double dt) const;
	
public:
	SimulationObject();
	virtual ~SimulationObject();
	
	virtual void StepTime(double dt) = 0;
	
	static void StepSimulation(double dt);
};

#endif
