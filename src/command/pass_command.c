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

//todo check error mdp
void check_password(char **command, int *new_socket, client_t *client)
{
    if (client->username == NULL) {
        dprintf(*new_socket, "%s %s\r\n", code_g[13].code, code_g[13].msg);
        return;
    } if (command[1] == NULL)
        command[1] = "";
    char *pass = command[1];

    for (size_t i = 0; clients_g[i].user != NULL; i++) {
        //printf("\"PASS = %s | username = %s\"\n", pass, client->username);
        if (strcmp(client->username, clients_g[i].user) == 0 
        && strcmp(pass, clients_g[i].pass) == 0) {
            dprintf(*new_socket, "%s %s\r\n", code_g[9].code, code_g[9].msg);
            client->status = LOGGED;
            return;
        }
    }
    dprintf(*new_socket, "%s %s\r\n", code_g[15].code, code_g[14].msg);
}
