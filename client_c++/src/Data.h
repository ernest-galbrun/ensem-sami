#include <vector>
#include "Vehicle.h"
#include <boost/optional.hpp>
#include <boost/thread/mutex.hpp>

#ifndef DATA_H
#define DATA_H

class Data {

	private:
        std::vector<Vehicle> data;
		boost::mutex dataLock;

	public:
        boost::optional<Vehicle> getVehicle(string name);
		void setAll(std::vector<Vehicle> data);
};

#endif
