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

//todo check error for the delete command. I think something going wrong with dup/dup2

void check_dele(char **command, int *new_socket, client_t *client)
{
    pid_t pid = fork();
    int init = dup(1);
    (void) client;

    if (pid == -1) {
        printf("Error: FORK failed\n");
        dprintf(*new_socket, "%s %s\r\n", code_g[2].code, code_g[2].msg);
        dprintf(*new_socket, "%s %s\r\n", code_g[7].code, code_g[7].msg);
        return;
    } if (pid == 0) {
        dup2(*new_socket, 1);
        execl("/bin/rm", command[1]);
        dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
    } else {
        dup2(1, init);
        dprintf(*new_socket, "%s %s\r\n", code_g[2].code, code_g[2].msg);
        dprintf(*new_socket, "%s %s\r\n", code_g[7].code, code_g[7].msg);
    }
}
