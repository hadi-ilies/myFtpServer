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
#include "prototype.h"
#include "server.h"

//todo have to ask victor if i need to connect directly if the user has no password 

void check_user(char **command, int *new_socket, client_t *client)
{
    char *name = strdup(command[1]);

    //for (size_t i = 0; clients_g[i].user != NULL; i++) {
        //if (strcmp(name, clients_g[i].user) == 0) {
            dprintf(*new_socket, "%s %s\r\n", code_g[12].code, code_g[12].msg);
            client->username = strdup(name);
           //if (strcmp(client->username, "Anonymous") == 0) {
           //     command[1] = "";
           //     check_password(command, new_socket, client);
           // }
        //    return;
        //}
    //}
    //dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
}