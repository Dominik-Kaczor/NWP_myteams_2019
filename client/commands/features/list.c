/*
** EPITECH PROJECT, 2020
** list
** File description:
** list
*/

#include "client.h"

int list_thread(const char **array, int counter)
{
    struct tm time;
    time_t gmttime;

    if (array[1] == NULL)
        return EXIT_SUCCESS;
    for (int i = 1; i < counter; i = i + 4) {
        strftime((char *)array[i + 2], sizeof(array[i + 2]),
        "%Y-%m-%d", &time);
        gmttime = timegm(&time);
        client_channel_print_threads(array[i], array[i + 1], gmttime,
        array[i + 3], array[i + 4]);
    }
    return EXIT_SUCCESS;
}

int list_channel(const char **array, int counter)
{
    if (array[1] == NULL)
        return EXIT_SUCCESS;
    for (int i = 1; i < counter; i = i + 3)
        client_team_print_channels(array[i], array[i + 1], array[i + 2]);
    return EXIT_SUCCESS;
}

int list_replie(const char **array, int counter)
{
    struct tm time;
    time_t gmttime;

    if (array[1] == NULL)
        return EXIT_SUCCESS;
    for (int i = 1; i < counter; i = i + 5) {
        strftime((char *)array[i + 2], sizeof(array[i + 2]),
        "%Y-%m-%d", &time);
        gmttime = timegm(&time);
        client_thread_print_replies(array[i], array[i + 1], gmttime,
        array[i + 3]);
    }
    return EXIT_SUCCESS;
}

int list_team(const char **array, int counter)
{
    printf("MAZ\n");
    if (array[1] == NULL)
        return EXIT_SUCCESS;
    for (int i = 1; i < counter; i = i + 3)
        client_print_teams(array[i], array[i + 1], array[i + 2]);
    return EXIT_SUCCESS;
}

int list(server_t *clients, const char **array)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (clients->team == NULL)
        return list_team(array, counter);
    if (clients->channel == NULL)
        return list_channel(array, counter);
    if (clients->thread == NULL)
        return list_thread(array, counter);
    return list_replie(array, counter);
}
