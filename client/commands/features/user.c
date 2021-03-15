/*
** EPITECH PROJECT, 2020
** user
** File description:
** user
*/

#include "client.h"

int user(server_t *clients, const char **array)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (clients->name == NULL)
        printf("You are not logged\n");
    else if (counter == 4) {
        client_print_user(array[1], array[2], atoi(array[3]));
    } else {
        printf("This user doesn't exist\n");
    }
    return EXIT_SUCCESS;
}
