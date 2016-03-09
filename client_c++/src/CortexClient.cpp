#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "SocketBoost.h"

using namespace std;

CortexClient::CortexClient() {
    this->socket = SocketBoost(this->data);
}

void CortexClient::init() {
    this->socket->setTimeToWait(1);

    this->socket.init("100.64.209.183", "1510");
}

Vehicle CortexClient::getXYPosition(string name) {
    return *this->data.getVehicle(name);
}

void CortexClient::stop() {
    this->socket.stop();
}

string CortexClient::getIp() {
    return this->socket.getIp();
}

void CortexClient::setIp(string ip) {
    this->socket.setIp(ip);
}

string CortexClient::getPort() {
    return this->socket.getPort();
}

void CortexClient::setPort(string port) {
    this->socket.setPort(port);
}

int CortexClient::getTimeToWait() {
    return this->socket.getTimeToWait();
}

void CortexClient::setTimeToWait(int timeToWait) {
    this->socket.setTimeToWait(timeToWait);
}
