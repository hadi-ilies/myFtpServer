/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define NB_CLIENT 20

typedef enum {
  GUESS,
  LOGGED
} status_t;  
typedef struct
{
    struct timeval tv;
    int sockfd;
    int fds[NB_CLIENT];
    fd_set readSet;
    fd_set writeSet;
    int opt;//i
    int set_sock_opt;
    struct sockaddr_in address;
    int addrlen;
    char buffer[4096];
    char *pwd;
} server_t;

typedef struct {
  const char *user;
  const char *pass;
} user_table_t;

typedef struct {
  const char *code;
  const char *msg;
} code_t;

typedef struct {
  char *pwd;
  char *old_pwd;
  char *username;
  int fd;
  status_t status;
} client_t;

typedef struct {
  status_t status;
  char *command;
  void (*func) (char **command, int *new_socket, client_t *client);
  size_t nb_args;
  bool optional_arg;
} commands_t;

static const user_table_t clients_g[] = 
{   
    {"Anonymous", ""}, 
    {"Hadi", "LOLdu93"},
    {NULL, NULL}
};

//todo have to write a better help message
//NOTE : macros > static const. 
static const code_t code_g[] =
{
    {"120", "Service ready in nnn minutes."},
    {"125", "Data connection already open; transfer starting."},
    {"150", "File status okay; about to open data connection."},
    {"200", "Command okay."},
    {"214", "commands available are : \nUSER\nPASS\nHELP\nPWD\nCWD\n"
    "CDUP\nNOPE\nQUIT\n"},
    {"220", "Service ready for new user."},
    {"221", "Service closing control connection."},
    {"226", "Closing data connection."},
    {"227", "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
    {"230", "User logged in, proceed."},
    {"250", "Requested file action okay, completed."},
    {"257", "\"PATHNAME\" created."},
    {"331", "User name okay, need password."},
    {"332", "Need account for login."},
    {"xxx", "Error"},
    {"530", "You must be logged to use this command"}
};

void check_user(char **command, int *new_socket, client_t *client);
void check_password(char **command, int *new_socket, client_t *client);
void check_quit(char **command, int *new_socket, client_t *client);
void check_noop(char **command, int *new_socket, client_t *client);
void check_cwd(char **command, int *new_socket, client_t *client);
void check_pwd(char **command, int *new_socket, client_t *client);
void check_cdup(char **command, int *new_socket, client_t *client);
void check_help(char **command, int *new_socket, client_t *client);
void check_list(char **command, int *new_socket, client_t *client);
void check_dele(char **command, int *new_socket, client_t *client);

//TODO check Error arguments
//todo create a var in struct to save nb arg and after that have to compare

static const commands_t command_g[] = 
{
    {GUESS, "USER", &check_user, 1, false},
    {GUESS, "PASS", &check_password, 1, false},
    {GUESS, "QUIT", &check_quit, 0, false},
    {LOGGED, "NOPE", &check_noop, 0, false},
    {LOGGED, "CWD", &check_cwd, 1, false},
    {LOGGED, "PWD", &check_pwd, 0, false},
    {LOGGED, "CDUP", &check_cdup, 0, false},
    {GUESS, "HELP", &check_help, 0, true},
    {LOGGED, "LIST", &check_list, 1, true},
    {GUESS, "EXIT", &check_quit, 0, false},
    {LOGGED, "DELE", &check_dele, 1, false},
    {GUESS, NULL, NULL, 0, false}
};