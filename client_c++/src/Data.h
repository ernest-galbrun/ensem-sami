#include <vector>
#include <mutex>
#include "Vehicle.h"
#include <boost/optional.hpp>

#ifndef DATA_H
#define DATA_H

class Data {

	private:
        std::vector<Vehicle> data;
		std::mutex dataLock;

	public:
        boost::optional<Vehicle> getVehicle(string name);
		void setAll(std::vector<Vehicle> data);
};

#endif
