#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Vehicle.h"
#include "Point.h"

using namespace std;

Vehicle::Vehicle(){}

Vehicle::Vehicle(string name, vector<float> float_32_data){

	int size = float_32_data.size() / 3;
	this->name = name;

	int i;
	for(i = 0; i < size; i++ ){

		points.push_back(Point(float_32_data[3*i],float_32_data[3*i+1],float_32_data[3*i+2]));

	}

}

void Vehicle::print_data(){

	int i = 0;
	cout << "Object : " << getName() << endl;

	for(i = 0; i < points.size(); i++){

		cout << "Coord x : " << points[i].x  << " ;";
		cout << "Coord y : " << points[i].y  << " ;";
		cout << "Coord z : " << points[i].z  << " ;" << endl;

	}

}

string Vehicle::getName(){

	return name;

}

vector<Point> Vehicle::getPoints(){

	return points;

}

