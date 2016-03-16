#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <boost/thread/mutex.hpp>

#include "Data.h"
#include "Vehicle.h"

using namespace std;
using std::vector;

Data::Data(){}

Vehicle Data::getVehicle(string name) {
    boost::lock_guard<boost::mutex> guard(dataLock);

    for (int i = 0; i < data.size(); i++) {
        if(data.at(i).getName().compare(name))
            return data.at(i);
    }

    return Vehicle();
}

void Data::setAll(vector<Vehicle> data) {
    boost::lock_guard<boost::mutex> guard(dataLock);
    this->data = data;
}
