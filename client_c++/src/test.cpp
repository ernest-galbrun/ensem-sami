#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"

using namespace std;

int main(int argc, char* argv[]) {
    CortexClient *client = new CortexClient();

    client->setIp("192.168.1.109");
    client->setPort("1510");
    client->setTimeToWait(1);
    client->init();



    while(1){
      for(string s : client->getVehiclesNames()){
        cout << s << endl;
      }
    }

    return 0;
}
