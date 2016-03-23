#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"

using namespace std;

int main(int argc, char* argv[]) {
    CortexClient *client = new CortexClient();

    client->setIp("192.168.1.109");
    client->setPort("1510");
    client->setTimeToWait(1000);
    client->init();



    while(1){
      sleep(2);
      vector<string> vehicleNames = client->getVehiclesNames();
      int i;
      for(i = 0; i < vehicleNames.size(); i++){
        cout << vehicleNames[i] << endl;
      }
    }

    return 0;
}
