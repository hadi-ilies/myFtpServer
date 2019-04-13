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

//todo check error for the ls command
void check_list(char **command, int *new_socket, client_t *client)
{
    pid_t pid = fork();
    int tmp = dup(1);

    (void) client;
    if (pid == -1) {
        dprintf(*new_socket, "%s %s\r\n", code_g[2].code, code_g[2].msg);
        dprintf(*new_socket, "%s %s\r\n", code_g[7].code, code_g[7].msg);
        return;
    } 
    dup2(*new_socket, STDOUT_FILENO);
    if (pid == 0) {
        execl("/bin/ls", command[1] == NULL ? "." : command[1]);
        dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
    } else {
            waitpid(pid, 0, WSTOPPED);
    }
    dup2(tmp, STDOUT_FILENO);
    dprintf(*new_socket, "%s %s\r\n", code_g[2].code, code_g[2].msg);
    //maybe i will need to add a new message here
}
