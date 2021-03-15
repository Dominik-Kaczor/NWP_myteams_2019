/*
** EPITECH PROJECT, 2020
** use
** File description:
** use
*/

#include "server.h"

int use(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    (void)actual;
    while (array[counter])
        counter++;
    if (clients[sender].name == NULL)
        return (send_client(clients[sender].fd, "/unauthorized"));
    if (counter == 3)
        return EXIT_SUCCESS;
    if (counter == 4)
        return EXIT_SUCCESS;
    if (counter == 2) {
        if (clients[sender].team == NULL)
            return use_team(&clients[sender], array[1]);
        if (clients[sender].channel == NULL)
            return use_thread(&clients[sender], array[1]);
        return use_channel(&clients[sender], array[1]);
    } else
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    return EXIT_SUCCESS;
}