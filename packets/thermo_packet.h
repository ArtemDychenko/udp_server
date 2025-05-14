#ifndef THERMO_PACKET_H
#define THERMO_PACKET_H

#include <stdint.h>
#define EPOCH_2024_OFFSET 1704067200

typedef struct
{
    uint32_t timestamp;
    uint16_t temperature;
    uint8_t power_status;
    uint8_t measurement_id;
    uint8_t checksum;
} ThermoPacket;

void thermo_print_packet(const ThermoPacket* pkt);

#endif //THERMO_PACKET_H
