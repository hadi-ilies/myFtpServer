/*
** EPITECH PROJECT, 2019
** active mode
** File description:
** active mode 
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
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "server.h"

static void stor(char **command, int *new_socket, int client_socket)
{
    int	fd_file = creat(command[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    char buffer[getpagesize()];

	if (fd_file != -1) {
        dprintf(*new_socket, "%s %s\n", code_g[20].code, code_g[20].msg);
        while (read(client_socket, buffer, getpagesize()) > 0)
            dprintf(fd_file, "%s", buffer);
        dprintf(*new_socket, "%s %s\n", code_g[21].code, code_g[21].msg);
	    close(fd_file);
    } else {
        dprintf(*new_socket, "%s %s\r\n", code_g[14].code, code_g[14].msg);
    }
}

void check_stor(char **command, int *new_socket, client_t *client)
{
    int fd = 0;
    
    if (client->mode == PASV) {
        fd = accept(client->server.sockfd, 
        (struct sockaddr *)&client->server.address, (socklen_t*) &client->server.addrlen);
        stor(command, new_socket, fd);
        close(fd);
        client->mode = NONE;
    } else if (client->mode == ACTIVE)
        stor(command, new_socket, fd);
    else
        dprintf(*new_socket, "%s %s\n", code_g[18].code, code_g[18].msg);
}