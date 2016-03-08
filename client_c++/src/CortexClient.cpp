#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "SocketBoost.h"

using namespace std;

CortexClient::CortexClient() {
    this->socket = new SocketBoost(1);
    this->data = new Data();
}

void CortexClient::init() {
    this->socket->init();
}

Vehicle CortexClient::getXYPosition(char *name) {
    return *this->data->getVehicle(name);
}

void CortexClient::stop() {
    this->socket->stop();
}
