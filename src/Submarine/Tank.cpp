#include <Submarine/Tank.h>

using namespace std;
using json = nlohmann::json;

Tank::Tank(en_opening_type opening_type, double capacity)
{
	this->opening_type = opening_type;
	this->capacity = capacity;
}

double Tank::Fill(const Fluid &fluid, double volume)
{
	const string &fluid_name = fluid.GetName();
	
	double incompressible_volume = 0;
	double total_volume = 0;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(!it->second.fluid->IsCompressible())
			incompressible_volume += it->second.volume;
		
		total_volume += it->second.volume;
	}
	
	if(opening_type==en_opening_type::CLOSED)
	{
		double filled;
		
		if(incompressible_volume >= capacity)
			return 0;
		
		if(!fluid.IsCompressible())
			filled = (volume <= capacity - incompressible_volume)?volume:capacity-incompressible_volume;
		else
			filled = incompressible_volume >=capacity ? 0:volume;
		
		if(filled>0)
		{
			if(content.find(fluid_name)==content.end())
				content[fluid_name] = { fluid.clone(), 0 };
			
			content[fluid_name].volume += filled;
		}
		
		return filled;
	}
	else if(opening_type==en_opening_type::TOP || opening_type==en_opening_type::BOTTOM)
	{
		if(content.find(fluid_name)==content.end())
			content[fluid_name] = { fluid.clone(), 0 };
		
		content[fluid_name].volume += volume;
		total_volume += volume;
		
		while(total_volume > capacity)
		{
			auto it_min_max = content.begin();
			double min_max_density = it_min_max->second.fluid->GetDensity();
			for(auto it = content.begin(); it!=content.end(); ++it)
			{
				if(opening_type==en_opening_type::TOP && it->second.fluid->GetDensity()<min_max_density)
					it_min_max = it;
				if(opening_type==en_opening_type::BOTTOM && it->second.fluid->GetDensity()>min_max_density)
					it_min_max = it;
			}
			
			if(total_volume - capacity >= it_min_max->second.volume)
			{
				content.erase(it_min_max);
				total_volume -= it_min_max->second.volume;
			}
			else
			{
				it_min_max->second.volume -= total_volume - capacity;
				total_volume -= total_volume - capacity;
			}
		}
		
		
		return volume;
	}
	
	return 0;
}

double Tank::Empty(const Fluid &fluid, double volume)
{
	auto it = content.find(fluid.GetName());
	if(it==content.end())
		return false;
	
	if(it->second.volume>=volume)
	{
		it->second.volume -= volume;
		return volume;
	}
	
	double v = it->second.volume;
	delete it->second.fluid;
	content.erase(it);
	return v;
}

double Tank::GetMass() const
{
	double mass = 0;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		mass += it->second.fluid->GetDensity() * it->second.volume;
	}
	
	return mass;
}

double Tank::GetVolume(const Fluid &fluid) const
{
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(it->first==fluid.GetName())
			return it->second.volume;
	}
	
	return 0;
}


json Tank::ToJson() const
{
	double incompressible_volume = 0;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(!it->second.fluid->IsCompressible())
			incompressible_volume += it->second.volume;
	}
	
	json j;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(!it->second.fluid->IsCompressible())
			j[it->first]["volume"] = it->second.volume;
		else
		{
			j[it->first]["pressure"] = it->second.volume / (capacity - incompressible_volume);
			j[it->first]["volume"] = it->second.volume;
		}
	}
	
	return j;
}
