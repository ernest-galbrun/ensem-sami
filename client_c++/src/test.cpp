#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"
#include "Vehicle.h"

using namespace std;

int main(int argc, char* argv[]) {
    CortexClient client;

    client.setIp("192.168.1.109");
    client.setPort("1510");
    client.setTimeToWait(200);
    client.init();



    while(1){
      sleep(2);
      vector<string> vehicleNames = client.getVehiclesNames();
      Vehicle myVehicle = client.getXYPosition("markerset_robot3");
      client.updatePointsName();
      int i;
      cout << "markerset_robot3" << endl;
      myVehicle.print_data();
      /*for(i = 0; i < myVehicle.getPoints(); i++){
        cout << vehicleNames[i] << endl;
        markerset_robot8
      }*/
    }

    return 0;
}
