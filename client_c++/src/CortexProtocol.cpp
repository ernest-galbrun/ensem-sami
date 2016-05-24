#include "CortexProtocol.h"

using namespace std;

int CortexProtocol::generatePacket(char* data, int data_size, uint16_t type, char* buffer) {
    packet_header * header = (packet_header *)buffer;
    header->packet_type = type;
    header->packet_size = data_size;
    char * packet_data = (char *)(header+1);
    strncpy(packet_data, data, data_size);
    return data_size+sizeof(packet_header);
}
