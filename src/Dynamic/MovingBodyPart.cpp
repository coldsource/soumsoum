#include <Dynamic/MovingBodyPart.h>
#include <Dynamic/MovingBodyComponent.h>
#include <Dynamic/MovingBody.h>

using namespace std;

MovingBodyPart::MovingBodyPart(const string &name, const Vector3D &position, double mass)
{
	this->name = name;
	this->position = position;
	this->mass = mass;
}

Vector3D MovingBodyPart::GetRelativePosition() const
{
	Vector3D rel_position = position;
	rel_position.Rotate(moving_body->GetAttitude());
	return rel_position;
}

Vector3D MovingBodyPart::GetAbsolutePosition() const
{
	return moving_body->GetPosition() + GetRelativePosition();
}

void MovingBodyPart::AddComponent(MovingBodyComponent *component)
{
	component->moving_body = moving_body;
	component->moving_body_part = this;
	
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
