#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Vehicle_Object.h"

using namespace std;

Vehicle_Object::Vehicle_Object(char ** name, float ** float_32_data, int points_number){

	this->name = name;
	*(this->points_number) = points_number;
	points = new Point*[points_number];
	
	int i;
	for(i = 0; i < points_number; i++){

		points[i] = new Point(float_32_data[i][0],float_32_data[i][1],float_32_data[i][2]);

	} 

}

Vehicle_Object::~Vehicle_Object(){

	int i;
	for(i = 0; i < *points_number; i++){

		delete points[i];

	}

	delete [] points;

}

void Vehicle_Object::print_data(){

	int i = 0;
	cout << "Object : " << getName() << endl;

	for(i = 0; i < *points_number; i++){

		cout << "Coord x : " << points[i]->getX()  << " ;";
		cout << "Coord y : " << points[i]->getY()  << " ;";
		cout << "Coord z : " << points[i]->getZ()  << " ;" << endl;	

	}

}

char * Vehicle_Object::getName(){

	return * name;

}

Point ** Vehicle_Object::getPoints(){

	return points;

}

int Vehicle_Object::getPointsNumber(){

	return *points_number;

}
