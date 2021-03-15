/*
** EPITECH PROJECT, 2020
** login
** File description:
** login
*/

#include "client.h"

int login(server_t *server, const char **array)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (counter == 1)
        client_error_already_exist();
    else if (counter == 4) {
        server->id = strdup(array[2]);
        server->name = strdup(array[1]);
        client_event_loggedin(array[2], array[1]);
        if (server->name == NULL)
            return EXIT_ERROR;
        modify_prompt(server);
    } else
        client_event_loggedin(array[2], array[1]);
    return EXIT_SUCCESS;
}
