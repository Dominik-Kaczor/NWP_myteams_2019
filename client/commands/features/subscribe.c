/*
** EPITECH PROJECT, 2020
** subscribe
** File description:
** subscribe
*/

#include "client.h"

int subscribe(server_t *clients, const char **array)
{
    (void)clients;
    int counter = 0;

    while (array[counter])
        counter++;
    if (counter == 1)
        client_error_already_exist();
    if (counter == 2)
        client_error_unknown_team(array[1]);
    if (counter == 3)
        client_print_subscribed(array[1], array[2]);
    return EXIT_SUCCESS;
}
