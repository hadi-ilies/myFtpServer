/*
** EPITECH PROJECT, 2019
** active mode
** File description:
** active mode
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "prototype.h"
#include "server.h"

static void stor(char **command, int *new_socket, int client_socket)
{
    int	fd_file = creat(command[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    char buffer[getpagesize()];

    if (fd_file != -1) {
        PRT_SE(*new_socket, code_g[20].code, code_g[20].msg);
        while (read(client_socket, buffer, getpagesize()) > 0)
            dprintf(fd_file, "%s", buffer);
        PRT_SE(*new_socket, code_g[21].code, code_g[21].msg);
        close(fd_file);
    } else
        PRT_SE(*new_socket, code_g[22].code, code_g[22].msg);
}

void check_stor(char **command, int *new_socket, client_t *client)
{
    int fd = 0;

    if (client->mode == PASV) {
        fd = accept(client->server.sockfd,
        (struct sockaddr *) &client->server.address,
        (socklen_t*) &client->server.addrlen);
        stor(command, new_socket, fd);
        close(fd);
        client->mode = NONE;
    } else if (client->mode == ACTIVE) {
        create_active_socket(client);
        stor(command, new_socket, client->server.sockfd);
        close(client->server.sockfd);
        client->mode = NONE;
    } else
        PRT_SE(*new_socket, code_g[18].code, code_g[18].msg);
}
