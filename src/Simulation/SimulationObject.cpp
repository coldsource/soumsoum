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
		if(it->obj == this)
		{
			simulation_objs.erase(it);
			break;
		}
	}
	
	g_mutex.unlock();
}

void SimulationObject::StepSimulation(double dt)
{
	lock_guard<std::mutex> lock(g_mutex);
	
	for(auto it = simulation_objs.begin(); it!=simulation_objs.end(); ++it)
	{
		if(it->thread_id==this_thread::get_id())
			it->obj->StepTime(dt);
	}
}

void SimulationObject::variable_sim(double *current, double target, double rate, double dt) const
{
	if(*current==target)
		return;
	
	if(*current<target)
	{
		*current += rate * dt;
		if(*current>target)
			*current = target;
	}
	else
	{
		*current -= rate * dt;
		if(*current<target)
			*current = target;
	}
}
