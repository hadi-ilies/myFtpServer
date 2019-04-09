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

#define NB_USER 2

static const client_t clients_g[] = 
{   
    {"Anonymous", ""}, 
    {"Hadi", "LOLdu93"}
};

//todo have to write a better help message
static const code_t code_g[] =
{
    {"120", "\nService ready in nnn minutes.\n"},
    {"125", "\nData connection already open; transfer starting.\n"},
    {"150", "\nFile status okay; about to open data connection.\n"},
    {"200", "\nCommand okay.\n"},
    {"214", "\nHelp message.\n"},
    {"220", "\nService ready for new user.\n"},
    {"221", "\nService closing control connection."},
    {"226", "\nClosing data connection.\n"},
    {"227", "\nEntering Passive Mode (h1,h2,h3,h4,p1,p2).\n"},
    {"230", "\nUser logged in, proceed.\n"},
    {"250", "\nRequested file action okay, completed.\n"},
    {"257", "\n\"PATHNAME\" created.\n"},
    {"331", "\nUser name okay, need password.\n"},
    {"332", "\nNeed account for login.\n"},
    {"xxx", "Error"}
};

//todo create a swrite func that avoid to enter the length of the string each times
//todo create a tab with all msg error
static void check_user(const char *name, int *new_socket)
{
    for (size_t i = 0; i < NB_USER; i++) {
        if (strstr(name, clients_g[i].user) != NULL) {
            write(*new_socket, code_g[12].code, strlen (code_g[12].code) + 1);
            write(*new_socket, code_g[12].msg, strlen(code_g[12].msg) + 1);
            return;
        }
    }
    write(*new_socket, code_g[13].code, strlen(code_g[13].code) + 1);
    write(*new_socket, code_g[13].msg, strlen(code_g[13].msg) + 1);
}

//todo strstr find another way LOL

static void check_password(const char *name, const char *pass, int *new_socket)
{
    for (size_t i = 0; i < NB_USER; i++)
        if (name != NULL && strstr(name, clients_g[i].user) == 0 
        && strstr(pass, clients_g[i].pass) == 0) {
            write(*new_socket, code_g[9].code, strlen (code_g[9].code) + 1);
            write(*new_socket, code_g[9].msg, strlen(code_g[9].msg) + 1);
            return;
        }
    write(*new_socket, code_g[14].code, strlen (code_g[14].code) + 1);
    write(*new_socket, code_g[14].msg, strlen(code_g[14].msg) + 1);
}

static void ftp_commands(char **command, int *new_socket, server_t *server)
{
    //TODO convert if forest to func pointer
    //todo remove username and replace it by a struct
    static char *username = NULL;

    if (strcmp("USER", command[0]) == 0) {
        check_user(command[1], new_socket);
        username = command[1];
    } 
    else if (strcmp("PASS", command[0]) == 0)
        check_password(username, command[0], new_socket);
    else if (strcmp("PWD", server->pwd) == 0)
        write(*new_socket, server->pwd, strlen(server->pwd));
    else if (strcmp("QUIT", command[0]) == 0)
        _exit(EXIT_SUCCESS);
    else 
        printf("bad command has been inserted\n");
}

static void exec_command(int *new_socket, server_t *server)
{
    while (read(*new_socket, server->buffer, 4096) > 0) {
        //print le message reçu
        char **command = split_c(server->buffer, ' ');
        ftp_commands(command, new_socket, server);
        printf("Buff : %s\n", server->buffer);
        memset(server->buffer, '\0', 4096);

        //envoi la réponse
        write(*new_socket, "[SERVER] reçu 5/5 !", 20);
        //send(new_socket, "[SERVER] reçu 5/5 !", sizeof("[SERVER] reçu 5/5 !"), 0);
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