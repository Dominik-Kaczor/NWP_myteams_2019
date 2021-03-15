/*
** EPITECH PROJECT, 2020
** unauthorized
** File description:
** unauthorized
*/

#include "client.h"

int unauthorized(server_t *client, const char **array)
{
    (void)client;
    (void)array;
    client_error_unauthorized();
    return EXIT_SUCCESS;
}