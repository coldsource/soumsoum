#include <Submarine/Tank.h>

using namespace std;
using json = nlohmann::json;

Tank::Tank(en_opening_type opening_type, double capacity, const Fluid *external_fluid)
{
	this->opening_type = opening_type;
	this->capacity = capacity;
	this->external_fluid = external_fluid;
}

Tank::~Tank()
{
	for(auto it = content.begin();it!=content.end();++it)
		delete it->second.fluid;
}

void Tank::SetOpening(en_opening_type opening_type)
{
	this->opening_type = opening_type;
}

void Tank::balance()
{
	if(opening_type==en_opening_type::CLOSED)
		return;
	
	if(!external_fluid)
		return;
	
	double total_volume = 0;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(it->second.fluid->IsCompressible())
			total_volume += it->second.volume / external_fluid->GetPressure();
		else
			total_volume += it->second.volume;
	}
	
	if(total_volume>capacity)
	{
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
			
			total_volume -= Empty(*it_min_max->second.fluid, total_volume-capacity);
		}
	}
	else if(total_volume<capacity)
	{
		if(external_fluid->IsCompressible())
			Fill(*external_fluid, (capacity-total_volume) * external_fluid->GetPressure());
		else
			Fill(*external_fluid, capacity-total_volume);
	}
}

double Tank::Fill(const Fluid &fluid, double volume)
{
	const string &fluid_name = fluid.GetName();
	
	double incompressible_volume = 0;
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(!it->second.fluid->IsCompressible())
			incompressible_volume += it->second.volume;
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
		
		balance();
		
		return volume;
	}
	
	return 0;
}

double Tank::Empty(const Fluid &fluid, double volume)
{
	auto it = content.find(fluid.GetName());
	if(it==content.end())
		return false;
	
	if(volume==-1)
		volume = it->second.volume;
	
	if(it->second.volume>volume)
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

double Tank::GetPressure() const
{
	if(opening_type==en_opening_type::CLOSED)
	{
		double incompressible_volume = 0, compressible_volume = 0;
		for(auto it = content.begin(); it!=content.end(); ++it)
		{
			if(!it->second.fluid->IsCompressible())
				incompressible_volume += it->second.volume;
			else
				compressible_volume += it->second.volume;
		}
		
		return compressible_volume / (capacity - incompressible_volume);
	}
	else
		return external_fluid->GetPressure();
}

void Tank::StepTime(double dt)
{
	balance();
}

json Tank::ToJson() const
{
	double pressure = GetPressure();
	
	json j;
	
	// Default init for easier parse in JS
	json empty;
	empty["volume"] = 0;
	empty["pressure"] = 0;
	
	j["air"] = empty;
	j["dioxygen"] = empty;
	j["carbon_dioxide"] = empty;
	j["water"] = empty;
	
	for(auto it = content.begin(); it!=content.end(); ++it)
	{
		if(!it->second.fluid->IsCompressible())
			j[it->first]["volume"] = it->second.volume;
		else
		{
			j[it->first]["pressure"] = pressure;
			j[it->first]["volume"] = it->second.volume;
		}
	}
	
	return j;
}
