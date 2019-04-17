/*
** EPITECH PROJECT, 2019
** QUIT
** File description:
** QUIT
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

void check_quit(char **command, int *new_socket, client_t *client)
{
    (void) command, (void) client;

    PRT_SE(*new_socket, code_g[6].code, code_g[6].msg);
    shutdown(*new_socket, SHUT_RDWR);
    close(*new_socket);
}
