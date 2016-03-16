#include <vector>
#include "Vehicle.h"
#include <boost/thread/mutex.hpp>

#ifndef DATA_H
#define DATA_H

class Data
{

	private:
		boost::mutex dataLock;
		std::vector<Vehicle> data;
  	Data(const Data & data);

	public:
		Data();
		Vehicle getVehicle(string name);
		void setAll(std::vector<Vehicle> data);
};

#endif
