#include <cstdlib>
#include <cstring>
#include <stdlib.h>

#include "CortexClient.h"

using namespace std;

int main(int argc, char* argv[]) {
    CortexClient *client = new CortexClient();

    client->init();

    while(1){}

    return 0;
}
