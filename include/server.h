/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct
{
    int sockfd;
    int opt;//i
    int set_sock_opt;
    struct sockaddr_in address;
    int addrlen;
    char buffer[4096];
} server_t;
