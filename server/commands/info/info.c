/*
** EPITECH PROJECT, 2020
** info
** File description:
** info
*/

#include "server.h"

int info(client_t *clients, int sender, const char **array, int actual)
{
    (void)actual;

    if (clients[sender].name == NULL)
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    if (array[1] != NULL)
        if (send_client(clients[sender].fd, "XXX Too many arguments") ==
        EXIT_ERROR)
            return EXIT_ERROR;
    if (clients[sender].team == NULL)
        return info_user(&clients[sender]);
    if (clients[sender].channel == NULL)
        return info_team(&clients[sender]);
    if (clients[sender].thread == NULL)
        return info_channel(&clients[sender]);
    return info_thread(&clients[sender]);
}