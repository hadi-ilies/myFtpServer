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

void check_quit(char **command, int *new_socket, client_t *client)
{
    (void) command, (void) client;

    dprintf(*new_socket, "%s %s\r\n", code_g[6].code, code_g[6].msg);
    shutdown(*new_socket, SHUT_RDWR);
    close(*new_socket);
}