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

static size_t count_args(char **command)
{
    size_t nb_args = 0;

    while (command[nb_args] != NULL)
        nb_args++;
    return nb_args - 1;
}

//todo strstr find another way to compare your char *
//todo add server as parameter of pointer on func because i need it in QUIT Func

static void ftp_commands(char **command, int *new_socket, server_t *server, client_t *client)
{
    for (size_t i = 0; command_g[i].command != NULL; i++) {
        if (strcmp(command[0], command_g[i].command) == 0)
            command_g[i].func(command, new_socket, client);
        if (strcmp(command[0], command_g[i].command) == 0 && strcmp(command[0], "QUIT") == 0)
            server->fds[client->fd] = -1;
    }
}

bool is_valid(char **command, int *new_socket, client_t *client)
{
    if (command == NULL || command[0] == NULL) {
        dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
        return false;
    } for (size_t i = 0; command_g[i].command != NULL; i++) {
        if (strcmp(command[0], command_g[i].command) == 0 
        && client->status == GUESS && command_g[i].status == LOGGED) {
            dprintf(*new_socket, "%s %s\r\n", code_g[15].code, code_g[15].msg);
            return false;
        } if (strcmp(command[0], command_g[i].command) == 0 && command_g[i].nb_args != count_args(command) && !command_g[i].optional_arg) {
            dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
            return false;
        }
    }
    return true;
}

static void exec_command(server_t *server, client_t *clients)
{
    //todo put global path or your stuff will not works because your client are'nt in the same directory

    for (int i = 0; i < NB_CLIENT; ++i) {
        if (server->fds[i] != -1 && FD_ISSET(server->fds[i], &server->readSet)) {
                read(server->fds[i], server->buffer, getpagesize());
                char **command = split_c(server->buffer, " \n\t\r");

                is_valid(command, &server->fds[i], &clients[i]) ? ftp_commands(command, &server->fds[i], server, &clients[i]) : 0;
                memset(server->buffer, '\0', 4096);
        }
    }
}

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

/**
 * NOTE : if getcwd parameter is NULL, the function will alloc a pointer and return the value wanted 
 * */

static void insert_path(server_t *server, client_t *client, char *path)
{
    chdir(server->pwd); //already checked
    chdir(path); // already cheched
    client->pwd = getcwd(NULL, 100);
}

void network_management(size_t port, char *path)
{
    server_t server = init_socket(port);
    client_t *clients = malloc(sizeof(client_t) * NB_CLIENT);
    int fd = -1;

    if (!clients)
        exit(84);
    while (1) {
        init_fd_sets(&server);
        int return_val = select(FD_SETSIZE, &server.readSet, &server.writeSet, NULL, &server.tv);

        if (return_val > 0 && FD_ISSET(server.sockfd, &server.readSet)) {
            (fd = new_client(&server)) == -1 ? EXIT_MSG(stderr, "too many many clients want to connect", 84) : 0;
            client_t client = {NULL, NULL, NULL, fd, GUESS};

            insert_path(&server, &client, path);
            clients[fd] = client; 
        }
        if (return_val > 0)
            exec_command(&server, clients);
    }
}