/*
** EPITECH PROJECT, 2019
** socket
** File description:
** socket
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "prototype.h"
#include "server.h"

server_t init_socket(size_t port)
{
    server_t server;
    struct timeval tv = {0};

    server.tv = tv;
    server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.opt = 0;
    server.set_sock_opt = SET_SOCK_OPT;
    server.addrlen = sizeof(server.address);
    memset(server.buffer, '\0', getpagesize());
    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(port);
    BIND;
    listen(server.sockfd, 6);
    server.pwd = getcwd(NULL, 100);
    server.ip_addr = inet_ntoa(server.address.sin_addr);
    for (size_t i = 0; i < NB_CLIENT; ++i)
        server.fds[i] = -1;
    return server;
}
