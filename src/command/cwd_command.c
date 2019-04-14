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

void check_cwd(char **command, int *new_socket, client_t *client)
{
    char *pass = command[1];
    char *tmp = getcwd(NULL, 100);

    if (chdir(pass) != 0) {
        dprintf(*new_socket, "%s %s\r\n", code_g[17].code, code_g[17].msg);
        return;
    }
    dprintf(*new_socket, "%s %s\r\n", code_g[10].code, code_g[10].msg);
    client->old_pwd = strdup(tmp);
    client->pwd = getcwd(NULL, 100);
}