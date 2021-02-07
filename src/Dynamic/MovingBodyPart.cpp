#include <Dynamic/MovingBodyPart.h>
#include <Dynamic/MovingBodyComponent.h>

using namespace std;

MovingBodyPart::MovingBodyPart(const string &name, double distance, double mass)
{
	this->name = name;
	this->distance = distance;
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
