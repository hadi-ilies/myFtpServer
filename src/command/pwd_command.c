/*
** EPITECH PROJECT, 2019
** pwd
** File description:
** pwd
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

void check_pwd(char **command, int *new_socket, client_t *client)
{
    (void) command;
    dprintf(*new_socket, "%s \"%s\" created\r\n", code_g[11].code,
    client->pwd);
}
