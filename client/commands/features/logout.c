/*
** EPITECH PROJECT, 2020
** logout
** File description:
** logout
*/

#include "client.h"

int logout(server_t *clients, const char **array)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (counter == 4) {
        client_event_loggedout(array[2], array[1]);
        clients->name = NULL;
        return EXIT_ERROR;
    } else
        client_event_loggedout(array[2], array[1]);
    return EXIT_SUCCESS;
}
