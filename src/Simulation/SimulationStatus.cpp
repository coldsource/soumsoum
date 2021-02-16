#include <Simulation/SimulationStatus.h>

using namespace std;

vector<SimulationStatus::obj_thread> SimulationStatus::simulation_objs;
std::mutex SimulationStatus::g_mutex;

using json = nlohmann::json;

SimulationStatus::SimulationStatus()
{
	g_mutex.lock();
	
	simulation_objs.push_back({this, this_thread::get_id()});
	
	g_mutex.unlock();
}

SimulationStatus::~SimulationStatus()
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

nlohmann::json SimulationStatus::GetStatus(double t)
{
	json j;
	
	g_mutex.lock();
	
	for(auto it = simulation_objs.begin(); it!=simulation_objs.end(); ++it)
	{
		if(it->thread_id==this_thread::get_id())
		{
			if(t - it->obj->last_update < it->obj->update_resolution)
				continue;
			
			it->obj->last_update = t;
			j[it->obj->GetName()] = it->obj->ToJson();
		}
	}
	
	g_mutex.unlock();
	
	return j;
}
