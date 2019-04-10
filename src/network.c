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
#include "prototype.h"
#include "server.h"

//todo strstr find another way LOL

static void ftp_commands(char **command, int *new_socket, server_t *server, client_t *client)
{
    for (size_t i = 0; command_g[i].command != NULL; i++) {
        if (strcmp(command[0], command_g[i].command) == 0 
        && client->status == GUESS && command_g[i].status == LOGGED) {
            dprintf(*new_socket, "%s You must be logged to use this command\n", code_g[14].code);
            continue;
        }
        if (strcmp(command[0], command_g[i].command) == 0)
            command_g[i].func(command, new_socket, client);
    }
}

static void exec_command(int *new_socket, server_t *server)
{
    client_t client = {server->pwd, NULL, NULL, GUESS};

    //todo put global path your stuff will not works if your client are'ent in the same dir
    if (chdir(client.pwd) == -1)
        EXIT_MSG(stderr, "Error: chdir", 84);
    while (read(*new_socket, server->buffer, 4096) > 0) {
        char **command = split_c(server->buffer, " \n\t\r");

        ftp_commands(command, new_socket, server, &client);
        printf("Buff : %s\n", server->buffer);
        memset(server->buffer, '\0', 4096);
        dprintf(*new_socket, "[SERVER] reçu 5/5 !\n");
    }
}

void network_management(size_t port, char *path)
{
    server_t server = init_socket(port, path);
    pid_t pid = 1;
    int new_socket = 0;
    
    while (1) {
        new_socket = accept(server.sockfd, 
        (struct sockaddr *)&server.address, (socklen_t*) &server.addrlen);
        pid = fork();    
        if (pid == -1)
            EXIT_MSG(stderr, "Fork error !", 84);//pid = fork();
        if (pid == 0) {
            printf("Client connected\n");
            exec_command(&new_socket, &server);
        }
    }
}