/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** prototype.h
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_
#include <stdlib.h>
#define EXIT_MSG(fd, str, ret) exit(fprintf(fd, "%s\n", str) * 0 + ret)  

// prototype
void network_management(size_t port, char *path);

#endif
