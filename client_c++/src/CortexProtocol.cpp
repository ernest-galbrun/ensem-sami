#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CortexProtocol.h"

using namespace std;

int CortexProtocol::generatePacket(char* data, uint16_t type, char* buffer) {
    strcpy(buffer, (char*)&type);
    strcpy(buffer+sizeof(uint16_t), (char*)strlen(data));
    strcpy(buffer+2*sizeof(uint16_t), data);

    return strlen(data)+2*sizeof(uint16_t);
}
