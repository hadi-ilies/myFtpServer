/*
** EPITECH PROJECT, 2019
** pasv command.c
** File description:
** pasv command.c
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
#include "server.h"
#include "prototype.h"

static void passive_msg(int *new_socket, server_t *server)
{
    size_t ip1 = 0;
    size_t ip2 = 0;
    size_t ip3 = 0;
    size_t ip4 = 0;
    char *ip = inet_ntoa(server->address.sin_addr);

    sscanf(ip, "%ld.%ld.%ld.%ld", &ip1, &ip2, &ip3, &ip4);
    printf("PORT = %d|IP = %s\n", server->port, ip);
    dprintf(*new_socket,
    "%s Entering Passive Mode (%ld,%ld,%ld,%ld,%d,%d).\r\n",
    code_g[8].code, ip1, ip2, ip3, ip4, server->port / 256, server->port % 256);
}

static int create_passive_socket(client_t *client)
{
    socklen_t len = sizeof(client->server.address);

    client->server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->server.sockfd == -1)
        EXIT_MSG(stderr, "Error: Fd error", 84);
    client->server.address.sin_family = AF_INET;
    client->server.address.sin_addr.s_addr = INADDR_ANY;
    client->server.address.sin_port = 0;
    if (bind(client->server.sockfd, (struct sockaddr*) &client->server.address,
        sizeof(client->server.address)) == -1)
        EXIT_MSG(stderr, "Error: bind failed", 84);
    if (listen(client->server.sockfd, 1) == -1)
        EXIT_MSG(stderr, "Error: listen failed", 84);
    if (getsockname(client->server.sockfd,
                    (struct sockaddr*)&client->server.address, &len) == -1)
        EXIT_MSG(stderr, "Error: getsockname failed", 84);
    return ntohs(client->server.address.sin_port);
}

void check_pasv(char **command, int *new_socket, client_t *client)
{
    (void) command;
    client->server.port = create_passive_socket(client);
    if (client->server.port == -1) {
        client->mode = NONE;
        client->server.sockfd = -1;
        PRT_SE(*new_socket, code_g[14].code, code_g[14].msg);
    } else {
        client->mode = PASV;
        passive_msg(new_socket, &client->server);
    }
}
