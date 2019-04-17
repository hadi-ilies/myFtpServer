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
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "prototype.h"
#include "server.h"

static int retrieve_port(char *command)
{
    size_t ip = 0;
    int	port1 = -1;
    int	port2 = -1;

    if (sscanf(command, "%ld,%ld,%ld,%ld,%d,%d",
    &ip, &ip, &ip, &ip, &port1, &port2) == -1)
        return -1;
    if (port1 <= 0 || port2 < 0)
        return (-1);
    printf("PORT Active : %d\n", port1 * 256 + port2);
    return (port1 * 256 + port2);
}

void create_active_socket(client_t *client)
{
    struct protoent *pe = getprotobyname("TCP");
    int useless = 1;
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
               (const char *)&useless, sizeof(useless));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(client->server.ip_addr);
    addr.sin_port = htons((uint16_t) client->server.port);
    if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
        printf("CONNECT ERROR\n");
    client->server.sockfd = sock;
}

void check_port(char **command, int *new_socket, client_t *client)
{
    if (command[1] == NULL) {
        PRT_SE(*new_socket, code_g[24].code, code_g[24].msg);
        return;
    }
    client->server.port = retrieve_port(command[1]);
    if (client->server.port == -1)
        PRT_SE(*new_socket, code_g[24].code, code_g[24].msg);
    else {
        PRT_SE(*new_socket, code_g[25].code, code_g[25].msg);
        client->mode = ACTIVE;
    }
}
