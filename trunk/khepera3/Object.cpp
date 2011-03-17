
#include "Object.h"

using namespace boost;

Object::Object(void):
	position(array<double,2>()),
	orientation(0)
{	
	for (int i=0;i<(int)position.size();++i)
		position[i] = 0;
}

Object::Object(vector<double> p, double orientation):
position(array<double,2>()),
orientation(orientation)
{	
	for (int i=0;i<(int)position.size();++i)
		position[i] = p[i];
}

Object::~Object(void)
{
}

void Object::InitLocalizationSystem(string bodyName){
	localizationSystem.FindBodyIndex(bodyName);
}

int Object::getId() const
{
	return id;
}

void Object::setId(int idArg)
{
	id = idArg;
}

array<double,2> Object::getPosition()
{
	return position;
}

void Object::setPosition(double xPosition, double yPosition)
{
	
	position[0] = xPosition;
	position[1] = yPosition;
}

double Object::getOrientation()
{
	return orientation;
}

void Object::setOrientation(double orientationArg)
{
	orientation = orientationArg;
}

bool Object::UpdatePosition() {
	return localizationSystem.UpdatePosition(&position, &orientation);
}