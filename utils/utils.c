#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/socket.h>


uint8_t calculate_checksum(ThermoPacket* pkt)
{
    uint8_t* ptr = (uint8_t*)pkt;
    size_t size = offsetof(ThermoPacket, checksum);
    uint8_t ckecksum = 0;
    for (size_t i = 0; i < size; i++)
    {
        ckecksum += ptr[i];
    }
    return ckecksum;
}

int initialize_server_socket(int port, struct sockaddr_in* servaddr)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(servaddr, 0, sizeof(*servaddr));
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = (INADDR_ANY);
    servaddr->sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr*)servaddr, sizeof(*servaddr)) < 0)
    {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}
