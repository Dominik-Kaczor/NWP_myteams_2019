/*
** EPITECH PROJECT, 2020
** info
** File description:
** info
*/

#include "client.h"

int info_thread(const char **array)
{
    struct tm time;
    time_t gmttime;

    if (array[1] == NULL)
        return EXIT_SUCCESS;
    strftime((char *)array[3], sizeof(array[3]),
    "%Y-%m-%d", &time);
    gmttime = timegm(&time);
    client_print_thread(array[1], array[2], gmttime,
    array[4], array[5]);
    return EXIT_SUCCESS;
}

int info_channel(const char **array)
{
    if (array[1] == NULL)
        return EXIT_SUCCESS;
    client_print_channel(array[1], array[2], array[3]);
    return EXIT_SUCCESS;
}

int info_user(const char **array)
{
    if (array[1] == NULL)
        return EXIT_SUCCESS;
    client_print_user(array[1], array[2], atoi(array[3]));
    return EXIT_SUCCESS;
}

int info_team(const char **array)
{
    if (array[1] == NULL)
        return EXIT_SUCCESS;
    client_print_team(array[1], array[2], array[3]);
    return EXIT_SUCCESS;
}

int info(server_t *clients, const char **array)
{
    (void)clients;
    if (clients->team == NULL)
        return info_user(array);
    if (clients->channel == NULL)
        return info_team(array);
    if (clients->thread == NULL)
        return info_channel(array);
    return info_thread(array);
}
