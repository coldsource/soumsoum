#include <Dynamic/MovingBodyPart.h>
#include <Dynamic/MovingBodyComponent.h>

using namespace std;

MovingBodyPart::MovingBodyPart(const string &name, const Vector3D &position, double mass)
{
	this->name = name;
	this->position = position;
	this->mass = mass;
}

void MovingBodyPart::AddComponent(MovingBodyComponent *component)
{
	components.push_back(component);
}

double MovingBodyPart::GetMass() const
{
	double mass = this->mass;
	
	for(auto it=components.begin(); it!=components.end(); ++it)
		mass += (*it)->GetMass();
	
	return mass;
}

map<string, Vector3D> MovingBodyPart::GetForces() const
{
	map<string, Vector3D> forces;
	
	for(auto it=components.begin(); it!=components.end(); ++it)
	{
		auto component_forces = (*it)->GetForces();
		for(auto it2 = component_forces.begin(); it2!=component_forces.end(); ++it2)
			forces[it2->first] = it2->second;
	}
	
	return forces;
}
