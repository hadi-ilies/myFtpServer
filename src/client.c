/*
** EPITECH PROJECT, 2019
** network
** File description:
** network
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "prototype.h"
#include "server.h"

int new_client(server_t *server)
{
    int new_socket = accept(server->sockfd,
    (struct sockaddr *)&server->address, (socklen_t*) &server->addrlen);

    printf("Client connected\n");
    for (size_t i = 0; i < NB_CLIENT; ++i)
        if (server->fds[i] == -1) {
            server->fds[i] = new_socket;
            PRT_SE(server->fds[i], code_g[5].code, code_g[5].msg);
            return i;
        }
    return -1;
}

static void insert_path(server_t *server, client_t *client, char *path)
{
    chdir(server->pwd);
    chdir(path);
    client->pwd = getcwd(NULL, 100);
    client->home = getcwd(NULL, 100);
}

client_t init_client(int fd, server_t *server, char *path)
{
    client_t client;

    client.fd = fd;
    client.home = NULL;
    client.pwd = NULL;
    client.old_pwd = NULL;
    client.username = NULL;
    client.status = GUESS;
    client.mode = NONE;
    client.server.address = server->address;
    client.server.ip_addr = inet_ntoa(server->address.sin_addr);
    insert_path(server, &client, path);
    return client;
}
