#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "SocketBoost.h"

using namespace std;

CortexClient::CortexClient() {
  SocketBoost socket = SocketBoost(data);
}

void CortexClient::init() {
  socket->setTimeToWait(1);

  socket.init("100.64.209.183", "1510");
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

void CortexClient::setTimeToWait(int timeToWait) {
  socket.setTimeToWait(timeToWait);
}
