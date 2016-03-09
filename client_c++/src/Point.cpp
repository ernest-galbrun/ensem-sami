#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Point.h"

Point::Point(int x, int y, int z){

	this->x = x;
	this->y = y;
	this->z = z;

}

Point::Point(int x, int y, int z, string name){

	this->x = x;
	this->y = y;
	this->z = z;
	this->name = name;

}

float Point::getX(){

	return x;

}

float Point::getY(){

	return y;

}

float Point::getZ(){

	return z;

}

string Point::getName(){

	return name;

}


void Point::setName(string name){

	this->name = name;

}
