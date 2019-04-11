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
#include "prototype.h"
#include "server.h"

//todo strstr find another way LOL
//todo add server as parameter of pointer on func because i need it in QUIT Func
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
        if (strcmp(command[0], command_g[i].command) == 0 && strcmp(command[0], "QUIT") == 0)
            server->fds[client->fd] = -1;
    }
}

static void exec_command(server_t *server, client_t *clients)
{
   // client_t client = {server->pwd, NULL, NULL, GUESS};

    //todo put global path your stuff will not works if your client are'ent in the same dir
   for (int i = 0; i < NB_CLIENT; ++i) {
        if (server->fds[i] != -1 && FD_ISSET(server->fds[i], &server->readSet)) {
                read(server->fds[i], server->buffer, 4096);
                char **command = split_c(server->buffer, " \n\t\r");
               
                ftp_commands(command, &server->fds[i], server, &clients[i]);
                //printf("Buff : %s\n", server->buffer);
                memset(server->buffer, '\0', 4096);
                //dprintf(*server->fds[i], "[SERVER] reçu 5/5 !\n");
        }
    }
}
//todo remove static
static void	init_fd_sets(server_t *server)
{
    FD_ZERO(&server->readSet);
    FD_ZERO(&server->writeSet);
    FD_SET(server->sockfd, &server->readSet);
    for (int i = 0; i < NB_CLIENT && server->fds[i] != -1 ; i++) {
        FD_SET(server->fds[i], &server->readSet);
        FD_SET(server->fds[i], &server->writeSet);
    }
}

//todo check error retuned by the function
static int new_client(server_t *server)
{    
    int new_socket = accept(server->sockfd, 
    (struct sockaddr *)&server->address, (socklen_t*) &server->addrlen);

    printf("Client connected\n");
    for (size_t i = 0; i < NB_CLIENT; ++i)
        if (server->fds[i] == -1) {
            server->fds[i] = new_socket;
            dprintf(server->fds[i], "%s %s\r\n", code_g[5].code, code_g[5].msg);
            return i;
        }
    return -1;
}

void network_management(size_t port, char *path)
{
    server_t server = init_socket(port, path);
    client_t *clients = malloc(sizeof(client_t) * NB_CLIENT);
    int new_socket = 0;
    int fd = -1;

    if (!clients)
        exit(84);
    while (1) {
        init_fd_sets(&server);
        int return_val = select(FD_SETSIZE, &server.readSet, &server.writeSet, NULL, &server.tv);
        
        if (return_val > 0) {
            if (FD_ISSET(server.sockfd, &server.readSet)) {
                fd = new_client(&server);
                fd == -1 ? EXIT_MSG(stderr, "too many many clients want to connect", 84) : 0;
                client_t client = {server.pwd, NULL, NULL, fd, GUESS};
                
                clients[fd] = client; 
            }
            exec_command(&server, clients);
        }
    }
}