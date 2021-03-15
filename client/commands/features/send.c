/*
** EPITECH PROJECT, 2020
** send
** File description:
** send
*/

#include "client.h"

int my_send(server_t *clients, const char **array)
{
    int counter = 0;

    (void)clients;
    while (array[counter])
        counter++;
    if (counter == 2)
        client_error_unknown_user(array[1]);
    else if (counter == 3)
        client_event_private_message_received(array[1], array[2]);
    return EXIT_SUCCESS;
}
