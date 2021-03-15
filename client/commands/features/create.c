/*
** EPITECH PROJECT, 2020
** create
** File description:
** create
*/

#include "client.h"

int create(server_t *clients, const char **array)
{
    int counter = 0;

    (void)clients;
    while (array[counter])
        counter++;
    if (counter == 1) {
        client_error_already_exist();
        return EXIT_SUCCESS;
    } else if (counter == 6) {
        if (strcmp(array[4], "team") == 0)
            client_print_team_created(array[2], array[1], array[3]);
        else
            client_print_channel_created(array[2], array[1], array[3]);
        return EXIT_SUCCESS;
    }
    if (strcmp(array[4], "team") == 0)
        client_event_team_created(array[2], array[1], array[3]);
    else
        client_event_channel_created(array[2], array[1], array[3]);
    return EXIT_SUCCESS;
}