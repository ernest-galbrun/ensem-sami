#ifndef CORTEX_H
#define CORTEX_H

#include "Vehicle.h"
#include "SocketBoost.h"
#include "Data.h"

class CortexClient {

    private:
        SocketBoost* socket;
        Data* data;

	public:
        CortexClient();
        void init();
        Vehicle* getXYPosition(char* name);
        void stop();
};

#endif
