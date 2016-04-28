#include <vector>
#include "Vehicle.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#ifndef DATA_H
#define DATA_H

using namespace std;
class Data
{

	private:
		boost::mutex dataLock;
		vector<Vehicle> data;
		vector<string> nameInfo;
		vector<int> posInfo;
		vector<string> getPointsNames(string name);

	public:
		Data();
  	Data(const Data & data);
		vector<string> getVehiclesNames();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);
		void setPointsNames(vector<string> nameInfo, vector<int> posInfo);

};

#endif
