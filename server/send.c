/*
** EPITECH PROJECT, 2020
** send
** File description:
** send
*/

#include "server.h"
#include <time.h>

int send_client(int sock, const char *buffer)
{
    fd_set wrfs;

    FD_ZERO(&wrfs);
    FD_SET(STDIN_FILENO, &wrfs);
    FD_SET(sock, &wrfs);
    if (select(sock + 1, NULL, &wrfs, NULL, NULL) == -1) {
        perror(BAD_SELECT);
        return EXIT_ERROR;
    }
    if (FD_ISSET(sock, &wrfs)) {
        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            perror(BAD_SEND);
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int my_send_history(client_t *clients, int sender, const char **array,
int actual)
{
    int i = 0;
    int j = 0;
    char **uids = get_list_array(clients);
    char *cmd = my_strcat(add_quotes(clients[sender].id), " ");

    cmd = my_strcat(cmd, add_quotes(array[2]));
    while (uids[j] != NULL && strcmp(uids[j], array[1]) != 0)
        ++j;
    if (uids[j] == NULL)
        return (send_client(clients[sender].fd,
            my_strcat("/send ", add_quotes(array[1]))));
    while (i < actual) {
        if (clients[i].id != NULL && strcmp(clients[i].id, array[1]) == 0) {
            send_client(clients[i].fd, my_strcat("/send ", cmd));
            break;
        }
        ++i;
    }
    message_file(clients, sender, array);
    return (0);
}

int my_send(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    if (clients[sender].name == NULL)
        return (send_client(clients[sender].fd, "/unauthorized"));
    while (array[counter])
        counter++;
    if (counter != 3)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    else if (strlen(array[2]) > MAX_BODY_LENGTH)
        return (send_client(clients[sender].fd, "XXX Too many characters"));
    else {
        if (my_send_history(clients, sender, array, actual) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}


int send_all_clients(client_t *clients, int actual, const char *buffer)
{
    for (int i = 0; i < actual; i++) {
        if (clients[i].name == NULL)
            continue;
        else if (send_client(clients[i].fd, buffer) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int send_choose_clients(client_t *clients, int sender,
int actual, const char *buffer)
{
    for (int i = 0; i < actual; i++) {
        if (sender == i || clients[i].name == NULL)
            continue;
        else if (send_client(clients[i].fd, buffer) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}