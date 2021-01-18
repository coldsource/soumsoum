#include <Simulation/SimulationObject.h>

using namespace std;

vector<SimulationObject::obj_thread> SimulationObject::simulation_objs;
std::mutex SimulationObject::g_mutex;

SimulationObject::SimulationObject()
{
	g_mutex.lock();
	
	simulation_objs.push_back({this, this_thread::get_id()});
	
	g_mutex.unlock();
}

SimulationObject::~SimulationObject()
{
	g_mutex.lock();
	
	for(auto it = simulation_objs.begin(); it!=simulation_objs.end(); ++it)
	{
		if((*it).obj == this)
		{
			simulation_objs.erase(it);
			break;
		}
	}
	
	g_mutex.unlock();
}

void SimulationObject::StepSimulation(double dt)
{
	g_mutex.lock();
	
	for(auto it = simulation_objs.begin(); it!=simulation_objs.end(); ++it)
	{
		if((*it).thread_id==this_thread::get_id())
			((*it).obj)->StepTime(dt);
	}
	
	g_mutex.unlock();
}
