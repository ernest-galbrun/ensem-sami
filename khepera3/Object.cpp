
#include "Object.h"

Object::Object(void)
{
	position = (double *)malloc(2);
}

Object::~Object(void)
{
}

int Object::getId()
{
	return id;
}

void Object::setId(int idArg)
{
	id = idArg;
}

double* Object::getPosition()
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