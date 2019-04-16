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
#include <errno.h>
#include <arpa/inet.h>
#include "prototype.h"
#include "server.h"

static int retrieve_port(char *command)
{
	size_t ip = 0;
	int	port1 = -1;
	int	port2 = -1;

	sscanf(command, "%ld,%ld,%ld,%ld,%d,%d", &ip, &ip, &ip, &ip, &port1, &port2);
	if (port1 <= 0 || port2 < 0)
		return (-1);
	return (port1 * 256 + port2);
}

static void create_active_socket(client_t *client)
{
    int useless = 1;
    int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		EXIT_MSG(stderr, "Error: Fd error", 84);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
    (const char *)&useless, sizeof(useless)) == -1)
		EXIT_MSG(stderr, "Error: socket error", 84);
	client->server.address.sin_family = AF_INET;
	client->server.address.sin_addr.s_addr = inet_addr("127.0.0.1");//client->server.ip_address);
	client->server.address.sin_port = htons(client->server.port);
	if (connect(sock, (const struct sockaddr *)&client->server.address, 
    sizeof(client->server.address)) == -1)
		EXIT_MSG(stderr, "Error: Connect error", 84);
    client->server.sockfd = sock;
}

void check_port(char **command, int *new_socket, client_t *client)
{
    if (command[1] == NULL) {
        dprintf(*new_socket, "%s %s\r\n", code_g[24].code, code_g[24].msg);
        return;
    }
    client->server.port = retrieve_port(command[1]);
    if (client->server.port == -1)
        dprintf(*new_socket, "%s %s\r\n", code_g[24].code, code_g[24].msg);
    else {
        dprintf(*new_socket, "%s %s\r\n", code_g[25].code, code_g[25].msg);
        create_active_socket(client);
        client->mode = ACTIVE;
    }
}