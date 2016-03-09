#include "Point.h"
#include <stdio.h>
#include<vector>
#include<string>

#ifndef VEHICLE_H
#define VEHICLE_H

using namespace std;

class Vehicle {

	private:
		string name;
		vector<Point> points;

	public:
		Vehicle(string name, vector<float> float_32_data);
		void print_data();
		vector<Point> getPoints();
		string getName();

};

#endif
