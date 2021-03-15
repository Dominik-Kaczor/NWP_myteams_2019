/*
** EPITECH PROJECT, 2020
** logout
** File description:
** logout
*/

#include "server.h"

int message_one_logout(client_t *clients, int sender)
{
    size_t len = sizeof(char) * (55 + strlen(clients[sender].name));
    char *message = malloc(len);

    strcpy(message, "/logout ");
    strcat(message, add_quotes(clients[sender].name));
    strcat(message, " ");
    strcat(message, add_quotes(clients[sender].id));
    strcat(message, " \"OK\"");
    message[len - 1] = '\0';
    if (send_client(clients[sender].fd, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int message_all_logout(client_t *clients, int sender, int actual)
{
    size_t len = sizeof(char) * (50 + strlen(clients[sender].name));
    char *message = malloc(len);

    strcpy(message, "/logout ");
    strcat(message, add_quotes(clients[sender].name));
    strcat(message, " ");
    strcat(message, add_quotes(clients[sender].id));
    message[len - 1] = '\0';
    if (send_choose_clients(clients, sender, actual, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int logout(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    while (array[counter])
        counter++;
    if (counter != 1)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    if (clients[sender].name == NULL)
        return (send_client(clients[sender].fd, "/unauthorized"));
    server_event_user_logged_out(clients[sender].id);
    if (message_one_logout(clients, sender) == EXIT_ERROR)
        return EXIT_ERROR;
    if (message_all_logout(clients, sender, actual) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}