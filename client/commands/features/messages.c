/*
** EPITECH PROJECT, 2020
** messages
** File description:
** messages
*/

#include "client.h"

time_t get_time(const char *time)
{
    time_t tStart;
    int yy, month, dd, hh, mm, ss;
    struct tm whenStart;

    sscanf(time, "%d-%d-%d %d:%d:%d", &yy, &month, &dd, &hh, &mm, &ss);
    whenStart.tm_year = yy - 1900;
    whenStart.tm_mon = month - 1;
    whenStart.tm_mday = dd;
    whenStart.tm_hour = hh;
    whenStart.tm_min = mm;
    whenStart.tm_sec = ss;
    whenStart.tm_isdst = -1;
    tStart = mktime(&whenStart);
    return tStart;
}

void display_messages(const char **array)
{
    int i = 1;

    while (array[i]) {
        client_private_message_print_messages(array[i],
        get_time(array[i + 2]), array[i + 1]);
        i += 3;
    }
}

int messages(server_t *clients, const char **array)
{
    (void)array;
    if (clients->name == NULL)
        printf("You are not logged\n");
    else {
        display_messages(array);
    }
    return EXIT_SUCCESS;
}
