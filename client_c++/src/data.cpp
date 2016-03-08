#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <mutex>
#include <vector>
#include <boost/optional.hpp>

#include "Data.h"
#include "Vehicle.h"

#define MAXDATA 2048

using namespace std;
using std::vector;
using std::mutex;
using std::lock_guard;

boost::optional<Vehicle> Data::getVehicle(char* name) {
    lock_guard<mutex> lock(this->dataLock);

    for (int i = 0; i < this->data.size(); i++) {
        if(this->compareVehicle(this->data.at(i), name)) {
            return boost::optional<Vehicle>(this->data.at(i));
        }
    }
    return boost::optional<Vehicle>();
}

void Data::setAll(vector<Vehicle> data) {
    lock_guard<mutex> lock(this->dataLock);
    this->data = data;
}

bool Data::compareVehicle(Vehicle v1, char* name) {
     return (std::strcmp(v1.getName(), name) == 0)? true: false;
}
