#ifndef CORTEX_PROTOCOL_H
#define CORTEX_PROTOCOL_H

#define NAME_PACKET 11
#define DATA_PACKET 13

#define REGULAR_MESSAGE 12
#define POINTS_NAME_MESSAGE 10

class CortexProtocol {
    public:
        typedef struct packet_header {
            uint16_t packet_type;
            uint16_t packet_size;
        } packet_header;

        int generatePacket(char* data, uint16_t type, char* buffer);
};

#endif
