/*
** EPITECH PROJECT, 2020
** list
** File description:
** list
*/

#include "server.h"

int list(client_t *clients, int sender, const char **array, int actual)
{
    (void)actual;
    if (clients[sender].name == NULL)
        return (send_client(clients[sender].fd, "/unauthorized"));
    if (array[1] != NULL)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    if (clients[sender].team == NULL)
        return list_team(clients[sender]);
    if (clients[sender].channel == NULL)
        return list_channel(&clients[sender]);
    if (clients[sender].thread == NULL)
        return list_thread(&clients[sender]);
    return list_replie(&clients[sender]);
}