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
#include "prototype.h"
#include "server.h"

static server_t init_socket(size_t port)
{
    server_t server;

    server.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.opt = 0;
    server.set_sock_opt = setsockopt(server.sockfd, SOL_SOCKET, 
    SO_REUSEADDR | SO_REUSEPORT, 
    (const char *)&server.opt, sizeof(server.opt));
    server.addrlen = sizeof(server.address);
    memset(server.buffer, '\0', 4096);
    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(port);
    bind(server.sockfd, (struct sockaddr *) &server.address, 
    sizeof(server.address));
    listen(server.sockfd, 6);
    return server;
}

void network_management(size_t port, char *path)
{
    server_t server = init_socket(port);
  
    //
    int new_socket = accept(server.sockfd, (struct sockaddr *)&server.address, (socklen_t*) &server.addrlen);

    while (read(new_socket, server.buffer, 4096) > 0) {
		//print le message reçu
		printf("%s\n", server.buffer);
		memset(server.buffer, '\0', 4096);

		//envoi la réponse
        write(new_socket, "[SERVER] reçu 5/5 !", 20);
		//send(new_socket, "[SERVER] reçu 5/5 !", sizeof("[SERVER] reçu 5/5 !"), 0);
	}
}