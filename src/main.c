/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include "prototype.h"

static const char *usage_g = "USAGE:\t./myftp <PORT> <PATH>\n\n"
"<PORT>\tthe port number on which the server socket listens\n"
"<PATH>\tthe path to the home directory for the Anonymous user\n";

static bool isanum(const char *str)
{
    if (!str)
        return false;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return (false);
    }
    return true;
}

static bool parsing(char **argv)
{
    DIR *fd = opendir(argv[2]);

    if (fd == NULL)
        return false;
    if (isanum(argv[1]) == false)
        return false;
    closedir(fd);
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        EXIT_MSG(stderr, usage_g, 84);
    if (parsing(argv) == false)
        EXIT_MSG(stderr, usage_g, 84);
    size_t port = atoi(argv[1]);
    char *path = argv[2];

    network_management(port, path);
    return (0);
}
