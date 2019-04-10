/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "server.h"

void check_password(char **command, int *new_socket, client_t *client)
{
    char *pass = command[1];

    for (size_t i = 0; clients_g[i].user != NULL; i++) {
        printf("\"PASS = %s | username = %s\"\n", pass, client->username);
        if (client->username != NULL && strstr(client->username, clients_g[i].user) != NULL
        && strstr(pass, clients_g[i].pass) != NULL) {
            dprintf(*new_socket, "%s\n", code_g[9].code);
            dprintf(*new_socket, "%s\n", code_g[9].msg);
            client->status = LOGGED;
            return;
        }
    }
    dprintf(*new_socket, "%s\n", code_g[14].code);
    dprintf(*new_socket, "%s\n", code_g[14].msg);
}
