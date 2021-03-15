/*
** EPITECH PROJECT, 2020
** subscribed
** File description:
** subscirbed
*/

#include "client.h"

void print_infos(const char **array)
{
    int i = 1;

    while (array[i]) {
        client_print_team(array[i + 1], array[i], array[i + 2]);
        i += 3;
    }
}

int subscribed(server_t *clients, const char **array)
{
    (void)array;

    if (clients->name == NULL)
        printf("You are not logged\n");
    else {
        print_infos(array);
    }
    return EXIT_SUCCESS;
}
