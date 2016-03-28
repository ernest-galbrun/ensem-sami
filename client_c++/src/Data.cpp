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
  boost::lock_guard<boost::mutex> guard(dataLock);
  int i;
  int size = data.size();
  vector<string> tempNames;
  tempNames.resize(size);

  for(i = 0 ; i < size; i++){
    cout << data[i].getName() << endl;
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

Vector<String> Data::getPointsNames(string name){
  int i;
  for(i = 0; i < posInfo.size(); i++){
    if(nameInfo[posInfo[i]].compare(name) == 0){
      Vector<String> v;
      int maxSize;
      if(i == posInfo.size() - 1){
        maxSize = nameInfo.size();
      }
      else{
        maxSize = posInfo[i+1];
      }
      v.resize(maxSize - (i + 1));
      int j;
      for(j = i + 1; j < maxSize; j++){
        v.push_back(nameInfo[j]);
      }
      return v;
    }
  }
  return null;
}

void Data::setPointsNames(){
  int i;
  for(i = 0; i < data.size(); i++){
    data[i].setPointsNames(getPointsNames);
  }
}

Data::Data(const Data & _data):dataLock(),data(_data.data){}

void Data::setAll(vector<Vehicle> data) {
  boost::lock_guard<boost::mutex> guard(dataLock);

  this->data.clear();
  this->data.reserve(data.size());
  this->data = data;

  //Checking if names of points do exist
  int i;
  bool needToRefresh = false;
  for(i = 0; i < data.size(); i++){
    if(getPointsNames(data[i].getName()) == null || getPointsNames(data[i].getName()).size() != data[i].getPoints().size()){
      needToRefresh = true;
      break;
    }
  }
  if(needToRefresh){
    //Call refresh procedure
  }
  setPointsNames();
}
