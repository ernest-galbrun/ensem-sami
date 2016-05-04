#ifndef CORTEX_H
#define CORTEX_H

#include "Vehicle.h"
#include "SocketBoost.h"
#include "Data.h"

class CortexClient {

  private:
    Data data;
    SocketBoost socket;

	public:
    CortexClient();

    void init();
    vector<string> getVehiclesNames();
    Vehicle getXYPosition(string name);
    // getVehicleNames() : liste de tous les véhicules présents
    void stop();

    string getIp();
    void setIp(string ip);

    void updatePointsName();

    string getPort();
    void setPort(string port);

    int getTimeToWait();
    void setTimeToWait(int timeToWait);

};

#endif
