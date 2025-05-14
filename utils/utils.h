#ifndef UTILS_H
#define UTILS_H
#include "../packets/thermo_packet.h"
#include <netinet/in.h>

uint8_t calculate_checksum(ThermoPacket* pkt);
int initialize_server_socket(int port, struct sockaddr_in* servaddr);

#endif //UTILS_H
