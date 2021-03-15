/*
** EPITECH PROJECT, 2020
** help
** File description:
** help
*/

#include "client.h"

int help(server_t *clients, const char **array)
{
    (void)clients;
    printf("%s", array[1]);
    return EXIT_SUCCESS;
}
