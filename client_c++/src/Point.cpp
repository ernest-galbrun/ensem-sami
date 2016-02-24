#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Point::Point(int x, int y, int z){

	this->x = x;
	this->y = y;
	this->z = z;

}

Point::Point(int x, int y, int z, char ** name){

	this->x = x;
	this->y = y;
	this->z = z;
	this->name = name;

}

float Point::GetX(){

	return x;

}

float Point::GetY(){

	return y;

}

float Point::GetZ(){

	return z;

}

char * Point::getName(){

	return * name;

}


void * Point::setName(char ** name){

	this->name = name;

}
