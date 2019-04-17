/*
** EPITECH PROJECT, 2019
** help
** File description:
** help
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

void check_help(char **command, int *new_socket, client_t *client)
{
    (void) command, (void) client;
    PRT_SE(*new_socket, code_g[4].code, code_g[4].msg);
}
