/*
** EPITECH PROJECT, 2019
** network
** File description:
** network
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "prototype.h"
#include "server.h"

static size_t count_args(char **command)
{
    size_t nb_args = 0;

    while (command[nb_args] != NULL)
        nb_args++;
    return nb_args - 1;
}

bool is_valid(char **command, int *new_socket, client_t *client)
{
    bool is_valid_command = false;

    if (command == NULL || command[0] == NULL)
        return PRT_SE(*new_socket, code_g[16].code, code_g[16].msg), false;
    for (size_t i = 0; command_g[i].command != NULL; i++) {
        if (strcmp(command[0], command_g[i].command) == 0)
            is_valid_command = true;
        if (strcmp(command[0], command_g[i].command) == 0
            && client->status == GUESS && command_g[i].status == LOGGED)
            return PRT_SE(*new_socket, code_g[15].code, code_g[15].msg), false;
        if (strcmp(command[0], command_g[i].command) == 0
            && command_g[i].nb_args != count_args(command)
            && !command_g[i].optional_arg)
            return PRT_SE(*new_socket, code_g[16].code, code_g[16].msg), false;
    } if (!is_valid_command)
        return PRT_SE(*new_socket, code_g[16].code, code_g[16].msg), false;
    return true;
}
