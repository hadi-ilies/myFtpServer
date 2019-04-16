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

// send_file --> read file
//  int fd_file = open(command[1], O_RDONLY);
//     FILE* file = fopen(command[1], "r"); /* should check the result 
//     char buff[getpagesize()];
//     void *buf;
//     struct  stat s;
    
//     if (file != NULL) {
//         fstat(fd_file, &s);
//         buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd_file, 0);
//         while (read)
//     while (fgets(buff, sizeof(buff), file)) {
//         /* note that fgets don't strip the terminating \n, checking its
//            presence would allow to handle lines longer that sizeof(line)
//         dprintf(client_socket, "%s", buff);
//     }
//         dprintf(*new_socket, "%s %s\n", code_g[20].code, code_g[20].msg);
//         dprintf(*new_socket, "%s %s\n", code_g[21].code, code_g[21].msg);
//         munmap(buf , s.st_size);
//     } else
//         dprintf(*new_socket, "%s %s\n", code_g[19].code, code_g[19].msg);


static void retr(char **command, int *new_socket, int client_socket)
{
    int fd_file = open(command[1], O_RDONLY);
    void *buf;
    struct  stat s;
    
    if (fd_file != -1) {
        fstat(fd_file, &s);
        buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd_file, 0);
        dprintf(client_socket, "%s", (char *) buf);
        dprintf(*new_socket, "%s %s\n", code_g[20].code, code_g[20].msg);
        dprintf(*new_socket, "%s %s\n", code_g[21].code, code_g[21].msg);
        munmap(buf , s.st_size);
    } else
        dprintf(*new_socket, "%s %s\n", code_g[19].code, code_g[19].msg);
}

void check_retr(char **command, int *new_socket, client_t *client)
{
    int fd = 0;
    
    if (client->mode == PASV) {
        fd = accept(client->server.sockfd, 
        (struct sockaddr *)&client->server.address, (socklen_t*) &client->server.addrlen);
        retr(command, new_socket, fd);
        close(fd);
        client->mode = NONE;
    } else if (client->mode == ACTIVE) {
        retr(command, new_socket, client->server.sockfd);
        close(client->server.sockfd);
        client->mode = NONE;
    } else
        dprintf(*new_socket, "%s %s\n", code_g[18].code, code_g[18].msg);
}