/*
** EPITECH PROJECT, 2020
** use
** File description:
** use
*/

#include "client.h"

int use(server_t *clients, const char **array)
{
    int counter = 0;

    while (array[counter++]);
    if (clients->team == NULL) {
        if (counter == 2)
            client_error_unknown_team(array[1]);
        else
            clients->team = strdup(array[2]);
    } else if (clients->channel == NULL) {
        if (counter == 2)
            client_error_unknown_channel(array[1]);
        else
            clients->channel = strdup(array[2]);
    } else {
        if (counter == 2)
            return client_error_unknown_thread(array[1]);
        else
            clients->thread = strdup(array[2]);
    }
    return EXIT_SUCCESS;
}