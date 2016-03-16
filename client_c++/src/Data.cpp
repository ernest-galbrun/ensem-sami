#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <boost/optional.hpp>
#include <boost/thread/mutex.hpp>

#include "Data.h"
#include "Vehicle.h"

using namespace std;
using std::vector;

boost::optional<Vehicle> Data::getVehicle(string name) {
    dataLock.lock();

    for (int i = 0; i < data.size(); i++) {
        if(data.at(i).getName().compare(name)) {
            dataLock.unlock();
            return boost::optional<Vehicle>(data.at(i));
        }
    }

    dataLock.unlock();
    return boost::optional<Vehicle>();
}

void Data::setAll(vector<Vehicle> data) {
    dataLock.lock();
    data = data;
    dataLock.unlock();
}
