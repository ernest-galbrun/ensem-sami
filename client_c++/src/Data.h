#include <vector>
#include "Vehicle.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#ifndef DATA_H
#define DATA_H

class Data
{

	private:
		boost::mutex dataLock;
		std::vector<Vehicle> data;

	public:
		Data();
  		Data(const Data & data);

		vector<string> getVehiclesNames();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);

};

#endif
