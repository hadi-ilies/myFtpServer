/*
** EPITECH PROJECT, 2019
** CDUP command
** File description:
** CDUP command
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

void check_cdup(char **command, int *new_socket, client_t *client)
{
    (void) command;
    if (chdir(client->old_pwd) != 0) {
        PRT_SE(*new_socket, code_g[15].code, code_g[15].msg);
        return;
    }
    PRT_SE(*new_socket, code_g[3].code, code_g[3].msg);
    client->pwd = strdup(client->old_pwd);

}
