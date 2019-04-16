/*
** EPITECH PROJECT, 2019
**
** File description:
**
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
#include "server.h"

//todo check error for the delete command. I think something going wrong with dup/dup2
//NOTE RETR == cat
void check_dele(char **command, int *new_socket, client_t *client)
{
    (void) client;
    if (access(command[1], F_OK) != 0) {
        dprintf(*new_socket, "%s %s\r\n", code_g[22].code, code_g[22].msg);
		return;
	}
	if (unlink(command[1]) == -1)
        dprintf(*new_socket, "%s %s\r\n", code_g[22].code, code_g[22].msg);
    dprintf(*new_socket, "%s %s\r\n", code_g[10].code, code_g[10].msg);
}
