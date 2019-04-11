/*
** socket.c for NWP_myftp_2018 in /Users/hadibereksi/Documents/Epitech/TEK2/NetworkProgramming/NWP_myftp_2018/src
**
** Made by test
** Login   <>
**
** Started on  Tue Apr 9 10:52:49 PM 2019 test
** Last update Tue Apr 9 10:52:49 PM 2019 test
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "prototype.h"
#include "server.h"

server_t init_socket(size_t port, char *path)
{
    server_t server = {{0}};

    server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.opt = 0;
    server.set_sock_opt = setsockopt(server.sockfd, SOL_SOCKET, 
    SO_REUSEADDR | SO_REUSEPORT, 
    (const char *)&server.opt, sizeof(server.opt));
    server.addrlen = sizeof(server.address);
    memset(server.buffer, '\0', 4096);
    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(port);
    bind(server.sockfd, (struct sockaddr *) &server.address, 
    sizeof(server.address));
    listen(server.sockfd, 6);
    server.pwd = path;
    for (size_t i = 0; i < NB_CLIENT; ++i)
        server.fds[i] = -1;
    return server;
}
//getcwd -> get cwd