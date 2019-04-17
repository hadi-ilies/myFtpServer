/*
** EPITECH PROJECT, 2019
** split
** File description:
** split
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **split_c(char *this, char *separator)
{
    size_t i = 0;
    char **array = malloc(sizeof(char *));

    if (array == NULL)
        return NULL;
    array[i] = strtok(this, separator);
    while (array[i] != NULL) {
        i++;
        array = realloc(array, sizeof(char *) * (i + 1));
        array[i] = strtok(NULL, separator);
    }
    return (array);
}
