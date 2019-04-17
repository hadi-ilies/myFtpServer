/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** prototype.h
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_
#include <stdlib.h>
#include "server.h"
#define EXIT_MSG(fd, str, ret) exit(fprintf(fd, "%s\n", str) * 0 + ret)
#define PRT_SE(x, y, z) dprintf(x, "%s %s\r\n", y, z)

void network_management(size_t port, char *path);
server_t init_socket(size_t port);
char **split_c(char *this, char *separator);
void create_active_socket(client_t *client);
int new_client(server_t *server);
client_t init_client(int fd, server_t *server, char *path);
bool is_valid(char **command, int *new_socket, client_t *client);
#endif
