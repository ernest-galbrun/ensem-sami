#ifndef CORTEX_H
#define CORTEX_H

#include "Vehicle.h"
#include "SocketBoost.h"
#include "Data.h"

class CortexClient {

    private:
        SocketBoost socket;
        Data data;

	public:
        void init();
        Vehicle getXYPosition(string name);
        void stop();

        string getIp();
        void setIp(string ip);

        string getPort();
        void setPort(string port);

        int getTimeToWait();
        void setTimeToWait(int timeToWait);

};

#endif
