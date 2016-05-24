#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "SocketBoost.h"

using namespace std;

CortexClient::CortexClient():socket(data){}

void CortexClient::init() {
  socket.init(getIp(), getPort(), getTimeToWait());
  sleep(1);//Wait for first values comming
}

vector<string> CortexClient::getVehiclesNames(){
  return data.getVehiclesNames();
}

Vehicle CortexClient::getXYPosition(string name) {
  return data.getVehicle(name);
}

void CortexClient::stop() {
  socket.stop();
}

string CortexClient::getIp() {
  return socket.getIp();
}

void CortexClient::setIp(string ip) {
  socket.setIp(ip);
  data.setIp(ip);
}

string CortexClient::getPort() {
  return socket.getPort();
}

void CortexClient::setPort(string port) {
    socket.setPort(port);
    data.setPort(port);
}

int CortexClient::getTimeToWait() {
  return socket.getTimeToWait();
}

void CortexClient::setTimeToWait(int timeToWait) {
  socket.setTimeToWait(timeToWait);
  data.setTimeToWait(timeToWait);
}
