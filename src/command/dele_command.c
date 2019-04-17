/*
** EPITECH PROJECT, 2019
** delete
** File description:
** delete
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "prototype.h"
#include "server.h"

void check_dele(char **command, int *new_socket, client_t *client)
{
    (void) client;
    if (access(command[1], F_OK) != 0) {
        PRT_SE(*new_socket, code_g[22].code, code_g[22].msg);
        return;
    } if (unlink(command[1]) == -1) {
        PRT_SE(*new_socket, code_g[22].code, code_g[22].msg);
        return;
    }
    PRT_SE(*new_socket, code_g[10].code, code_g[10].msg);
}
