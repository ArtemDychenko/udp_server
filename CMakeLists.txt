cmake_minimum_required(VERSION 3.28)
project(udp_server C)

set(CMAKE_C_STANDARD 11)

add_executable(udp_server main.c
        packets/thermo_packet.h
        packets/thermo_packet.c
        utils/utils.h
        utils/utils.c)
