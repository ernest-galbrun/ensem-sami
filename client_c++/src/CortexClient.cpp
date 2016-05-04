#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "SocketBoost.h"

using namespace std;

CortexClient::CortexClient():socket(data),data(*this) {}

void CortexClient::init() {
  socket.init(getIp(), getPort(), getTimeToWait());
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
}

string CortexClient::getPort() {
  return socket.getPort();
}

void CortexClient::setPort(string port) {
    socket.setPort(port);
}

int CortexClient::getTimeToWait() {
  return socket.getTimeToWait();
}

void CortexClient::updatePointsName(){
  socket.getPointsName();
}

void CortexClient::setTimeToWait(int timeToWait) {
  socket.setTimeToWait(timeToWait);
}
