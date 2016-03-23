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

vector<string> Data::getVehiclesNames(){
  int i;
  int size = data.size();
  vector<string> tempNames;
  tempNames.resize(size);
  for(int i = 0 ; i < size; i++){
    tempNames.push_back(data[i].getName());
  }
  return tempNames;
}

Vehicle Data::getVehicle(string name) {
    boost::lock_guard<boost::mutex> guard(dataLock);

    for (int i = 0; i < data.size(); i++) {
        if(data.at(i).getName().compare(name))
            return data.at(i);
    }

    return Vehicle();
}

Data::Data(const Data & _data):dataLock(),data(_data.data){}

void Data::setAll(vector<Vehicle> data) {
    boost::lock_guard<boost::mutex> guard(dataLock);
    this->data = data;
}
