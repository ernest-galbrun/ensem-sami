#ifndef DATA_H
#define DATA_H

#include <vector>
#include "Vehicle.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include "CortexClient.h"

using namespace std;
class Data
{

	private:
		CortexClient & client;
		boost::mutex dataLock;
		vector<Vehicle> data;
		vector<string> nameInfo;
		vector<int> posInfo;
		vector<string> getPointsNames(string name);
		void setPointsNames(vector<string> nameInfo, vector<int> posInfo);

	public:
		Data();
  	Data(const Data & data);
		vector<string> getVehiclesNames();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);

};

#endif
