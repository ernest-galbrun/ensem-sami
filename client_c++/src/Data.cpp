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
#include "CortexClient.h"

using namespace std;
using std::vector;

Data::Data(CortexClient& client):client(client){}

vector<string> Data::getVehiclesNames(){
  boost::lock_guard<boost::mutex> guard(dataLock);
  int i;
  int size = data.size();
  vector<string> tempNames;
  tempNames.reserve(size);

  for(i = 0 ; i < size; i++){
    tempNames.push_back(data[i].getName());
  }
  return tempNames;
}

Vehicle Data::getVehicle(string name) {
  boost::lock_guard<boost::mutex> guard(dataLock);

  for (int i = 0; i < data.size(); i++) {
      if(data.at(i).getName().compare(name) == 0)
          return data.at(i);
  }

  return Vehicle();
}

vector<string> Data::getPointsNames(string name){
  int i;
  vector<string> v;
  for(i = 0; i < posInfo.size(); i++){
    if(nameInfo[posInfo[i]].compare(name) == 0){
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
  return v;
}

void Data::setPointsNames(vector<string> nameInfo, vector<int> posInfo){
  this->nameInfo.clear();
  this->posInfo.clear();
  this->data.reserve(nameInfo.size());
  this->data.reserve(posInfo.size());
  this->nameInfo = nameInfo;
  this->posInfo = posInfo;
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
    if(getPointsNames(data[i].getName()).size() == 0 || getPointsNames(data[i].getName()).size() != data[i].getPoints().size()){
      needToRefresh = true;
      break;
    }
  }
  if(needToRefresh){
    client.updatePointsName();
  }
  for(i = 0; i< data.size(); i++){
    setPointsNames(data[i].getPointsNames(data[i].name));
  }

}
