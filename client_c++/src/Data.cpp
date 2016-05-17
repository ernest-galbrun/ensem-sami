#include "Data.h"
#include "SocketBoost.h"

using namespace std;
using std::vector;

Data::Data(){}

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
      if(data[i].getName().compare(name) == 0){
          return data[i];
      }
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
      int j;
      for(j = posInfo[i] + 1; j < maxSize; j++){
        v.push_back(nameInfo[j]);
      }
      return v;
    }
  }
  return v;
}

void Data::setPointsNames(vector<string> nameInfo, vector<int> posInfo){
  boost::lock_guard<boost::mutex> guard(dataLockName);
  this->nameInfo.clear();
  this->posInfo.clear();
  this->nameInfo = nameInfo;
  this->posInfo = posInfo;
}

Data::Data(const Data & _data):dataLock(),dataLockName(),data(_data.data){}

void Data::setAll(vector<Vehicle> data) {

  boost::lock_guard<boost::mutex> guard(dataLock);

  this->data.clear();
  this->data.reserve(data.size());
  this->data = data;

  //Checking if names of points do exist
  int i;
  bool needToRefresh = false;
  for(i = 0; i < this->data.size(); i++){
    if(getPointsNames(this->data[i].getName()).size() == 0 || getPointsNames(this->data[i].getName()).size() != this->data[i].getPoints().size()){
      needToRefresh = true;
      break;
    }
  }
  if(needToRefresh){
    SocketBoost name_socket(*this);
    name_socket.init_name(ip, port, timeToWait);
  }
  int j;
  boost::lock_guard<boost::mutex> guardName(dataLockName);
  for(i = 0; i< this->data.size(); i++){
    this->data[i].setPointsNames(getPointsNames(this->data[i].getName()));
  }
}

void Data::setIp(string ip) {
	this->ip = ip;
}

void Data::setPort(string port) {
	this->port = port;
}

void Data::setTimeToWait(int timeToWait) {
	this->timeToWait = timeToWait;
}
