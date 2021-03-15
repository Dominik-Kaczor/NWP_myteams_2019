/*
** EPITECH PROJECT, 2020
** users
** File description:
** users
*/

#include "client.h"

int users(server_t *clients, const char **array)
{
    (void)array;
    if (clients->name == NULL) {
        printf("You are not logged\n");
    } else {
        for (int i = 1; array[i] != NULL; i += 3) {
            client_print_users(array[i], array[i + 1], atoi(array[i + 2]));
        }
    }
    return EXIT_SUCCESS;
}
