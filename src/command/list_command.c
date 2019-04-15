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
#include <sys/types.h>
#include <sys/wait.h> 
#include <errno.h>
#include "server.h"

//todo check error for the ls command
static void list(char **command, int *new_socket, int client_socket)
{
    pid_t pid = fork();
    int tmp = dup(STDOUT_FILENO);

    if (pid == -1) {
        dprintf(*new_socket, "%s %s\r\n", code_g[2].code, code_g[2].msg);
        dprintf(*new_socket, "%s %s\r\n", code_g[7].code, code_g[7].msg);
        return;
    }
    dup2(client_socket, STDOUT_FILENO);
    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", command[1] == NULL ? "." : command[1], NULL);
        dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
    } else {
        waitpid(pid, 0, WSTOPPED);
    }
    dup2(tmp, STDOUT_FILENO);
    dprintf(*new_socket, "%s %s\r\n", code_g[20].code, code_g[20].msg);
    dprintf(*new_socket, "%s %s\r\n", code_g[21].code, code_g[21].msg);
}

void check_list(char **command, int *new_socket, client_t *client)
{
    int fd = 0;
    
    if (client->mode == PASV) {
        fd = accept(client->server.sockfd, 
        (struct sockaddr *)&client->server.address, (socklen_t*) &client->server.addrlen);
        list(command, new_socket, fd);
        client->mode = NONE;
    } else if (client->mode == ACTIVE)
        list(command, new_socket, fd);
    else
        dprintf(*new_socket, "%s %s\n", code_g[18].code, code_g[18].msg);
}
