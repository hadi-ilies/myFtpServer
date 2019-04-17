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

static void ftp_command(char **command, int *new_socket,
                        server_t *server, client_t *client)
{
    for (size_t i = 0; command_g[i].command != NULL; i++) {
        if (strcmp(command[0], command_g[i].command) == 0)
            command_g[i].func(command, new_socket, client);
        if (strcmp(command[0], command_g[i].command) == 0
            && strcmp(command[0], "QUIT") == 0)
            server->fds[client->fd] = -1;
    }
}

static void exec_command(server_t *server, client_t *clients)
{
    for (int i = 0; i < NB_CLIENT; ++i) {
        if (server->fds[i] != -1
            && FD_ISSET(server->fds[i], &server->readSet)) {
            FILE *fd = fdopen(server->fds[i], "r");

            fgets(server->buffer, getpagesize(), fd);
            char **command = split_c(server->buffer, " \n\t\r");

            is_valid(command, &server->fds[i], &clients[i]) ?
                ftp_command(command, &server->fds[i], server, &clients[i]) : 0;
            memset(server->buffer, '\0', getpagesize());
        }
    }
}

static void init_fd_sets(server_t *server)
{
    FD_ZERO(&server->readSet);
    FD_ZERO(&server->writeSet);
    FD_SET(server->sockfd, &server->readSet);
    for (int i = 0; i < NB_CLIENT && server->fds[i] != -1 ; i++) {
        FD_SET(server->fds[i], &server->readSet);
        FD_SET(server->fds[i], &server->writeSet);
    }
}
/**
 * NOTE : if getcwd parameter is NULL, the function will alloc a pointer and return the value wanted
 **/
void network_management(size_t port, char *path)
{
    server_t server = init_socket(port);
    client_t *clients = malloc(sizeof(client_t) * NB_CLIENT);
    int fd = -1;

    if (!clients)
        exit(84);
    while (1) {
        init_fd_sets(&server);
        int return_val = select(FD_SETSIZE, &server.readSet,
                                &server.writeSet, NULL, &server.tv);

        if (return_val > 0 && FD_ISSET(server.sockfd, &server.readSet)) {
            (fd = new_client(&server)) == -1 ?
                EXIT_MSG(stderr, "too many people want to connect", 84) : 0;
            client_t client = init_client(fd, &server, path);

            clients[fd] = client;
        } if (return_val > 0)
              exec_command(&server, clients);
    }
}
