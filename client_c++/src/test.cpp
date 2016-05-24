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

    int input = 0;
    sleep(3);
    while(input != -1){
      vector<string> vehicleNames = client.getVehiclesNames();
      cout << "Select vehicle number or use -1 to exit" << endl;
      for(int i = 1; i < (vehicleNames.size() +1); i++) {
          cout << i << " " << vehicleNames[i -1] << "\n";
      }

      input = 0;
      cout << "Vehicle number : ";
      cin >> input;

      if(input < vehicleNames.size())client.getXYPosition(vehicleNames[input-1]).print_data();
    }

    return 0;
}
