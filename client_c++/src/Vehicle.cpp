#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Vehicle.h"
#include "Point.h"

using namespace std;

Vehicle::Vehicle(string name, vector<float> float_32_data){

	int size = float_32_data.size() / 3;
	this->name = name;
	points.reserve(size);

	int i;
	for(i = 0; i < size; i++ ){

		points[i] = Point(float_32_data[3*i],float_32_data[3*i+1],float_32_data[3*i+2]);

	}

}

void Vehicle::print_data(){

	int i = 0;
	cout << "Object : " << getName() << endl;

	for(i = 0; i < points.size(); i++){

		cout << "Coord x : " << points[i].getX()  << " ;";
		cout << "Coord y : " << points[i].getY()  << " ;";
		cout << "Coord z : " << points[i].getZ()  << " ;" << endl;

	}

}

string Vehicle::getName(){

	return name;

}

vector<Point> Vehicle::getPoints(){

	return points;

}

