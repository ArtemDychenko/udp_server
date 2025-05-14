#include "thermo_packet.h"

#include <stdio.h>
#include <time.h>

void thermo_print_packet(const ThermoPacket* pkt)
{
    char time_buffer[80];
    time_t actual_time = pkt->timestamp + EPOCH_2024_OFFSET;
    struct tm* timeinfo = localtime(&actual_time);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("Thermometer: time: %s, temp: %.1f °C, power: %s, id: %u, checksum: %u\n",
           time_buffer,
           pkt->temperature / 10.0,
           pkt->power_status ? "Battery" : "Mains power supply",
           pkt->measurement_id,
           pkt->checksum);
}
