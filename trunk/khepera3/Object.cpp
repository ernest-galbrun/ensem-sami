
#include "Object.h"

using namespace boost;

Object::Object(void):
	position(array<double,2>()),
	orientation(0)
{	
	for (int i=0;i<(int)position.size();++i)
		position[i] = 0;
}

Object::~Object(void)
{
}

void Object::InitLocalizationSystem(string myAddress, string hostAddress, string bodyName){
	localizationSystem.init(myAddress, hostAddress, bodyName, &position, &orientation);
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