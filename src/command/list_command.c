/*
** EPITECH PROJECT, 2019
** list_command
** File description:
** list_command
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

static void list(char **command, int *new_socket, int client_socket)
{
    pid_t pid = fork();
    int tmp = dup(STDOUT_FILENO);

    if (pid == -1) {
        PRT_SE(*new_socket, code_g[2].code, code_g[2].msg);
        PRT_SE(*new_socket, code_g[7].code, code_g[7].msg);
        return;
    }
    dup2(client_socket, STDOUT_FILENO);
    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", command[1], NULL);
        perror("execl");
        PRT_SE(*new_socket, code_g[14].code, code_g[14].msg);
    } else
        waitpid(pid, 0, WSTOPPED);
    dup2(tmp, STDOUT_FILENO);
    PRT_SE(*new_socket, code_g[20].code, code_g[20].msg);
    PRT_SE(*new_socket, code_g[21].code, code_g[21].msg);
}

void check_list(char **command, int *new_socket, client_t *client)
{
    int fd = 0;

    if (client->mode == PASV) {
        fd = accept(client->server.sockfd,
        (struct sockaddr *)&client->server.address,
        (socklen_t*) &client->server.addrlen);
        list(command, new_socket, fd);
        close(fd);
        client->mode = NONE;
    } else if (client->mode == ACTIVE) {
        create_active_socket(client);
        printf("fd = %d\n", client->server.sockfd);
        list(command, new_socket, client->server.sockfd);
        close(client->server.sockfd);
        client->mode = NONE;
    } else
        PRT_SE(*new_socket, code_g[18].code, code_g[18].msg);
}
