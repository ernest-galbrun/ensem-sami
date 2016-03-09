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
    this->dataLock.lock();

    for (int i = 0; i < this->data.size(); i++) {
        if(this->data.at(i).getName().compare(name)) {
            this->dataLock.unlock();
            return boost::optional<Vehicle>(this->data.at(i));
        }
    }

    this->dataLock.unlock();
    return boost::optional<Vehicle>();
}

void Data::setAll(vector<Vehicle> data) {
    this->dataLock.lock();
    this->data = data;
    this->dataLock.unlock();
}
