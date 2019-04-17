/*
** EPITECH PROJECT, 2019
** user
** File description:
** user
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

void check_user(char **command, int *new_socket, client_t *client)
{
    char *name = strdup(command[1]);

    PRT_SE(*new_socket, code_g[12].code, code_g[12].msg);
    client->username = strdup(name);
}
