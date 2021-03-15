/*
** EPITECH PROJECT, 2020
** creates
** File description:
** create
*/

#include "server.h"

int choose_create(client_t *clients, int sender, const char **array, int actual)
{
    if (clients[sender].team == NULL)
        return (team_managment(clients, sender, array, actual));
    if (clients[sender].channel == NULL)
        return (channel_managment(clients, sender, array, actual));
    if (clients[sender].thread == NULL)
        return (thread_managment(clients, sender, array, actual));
    return EXIT_SUCCESS;
}

int create(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (clients[sender].name == NULL)
        return (send_client(clients[sender].fd, "/unauthorized"));
    if (counter != 3)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    if (strlen(array[1]) > MAX_NAME_LENGTH)
        return (send_client(clients[sender].fd, "XXX Name is too long"));
    if (strlen(array[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_client(clients[sender].fd, "XXX Descript is too long"));
    return choose_create(clients, sender, array, actual);
}