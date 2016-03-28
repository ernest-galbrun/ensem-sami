#include <vector>
#include "Vehicle.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

using namespace std;

#ifndef DATA_H
#define DATA_H

class Data
{

	private:
		boost::mutex dataLock;
		vector<Vehicle> data;
		Vector<String> nameInfo;
		Vector<int> posInfo;
		Vector<String> getPointsNames(string name);
		void setPointsNames();

	public:
		Data();
  		Data(const Data & data);

		vector<string> getVehiclesNames();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);

};

#endif
