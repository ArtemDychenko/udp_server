#include <errno.h>

#include "packets/thermo_packet.h"
#include "utils/utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#define PORT 12345


volatile sig_atomic_t running = 1;

void sig_handler(int sig)
{
    running = 0;
}

int main()
{
    signal(SIGINT, sig_handler);

    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    ThermoPacket pkt;


    int sockfd = initialize_server_socket(PORT, &servaddr);
    if (sockfd < 0)
    {
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Error setting timeout");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    while (running)
    {
        ssize_t n = recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*)&cliaddr, &len);
        if (n < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue;
            }

            perror("recvfrom");
            continue;
        }

        uint8_t expected = calculate_checksum(&pkt);
        if (pkt.checksum != expected)
        {
            printf("Serwer: Invalid checksum (got %u, expected %u)\n", pkt.checksum, expected);
            continue;
        }

        thermo_print_packet(&pkt);
    }

    close(sockfd);
    return 0;
}
