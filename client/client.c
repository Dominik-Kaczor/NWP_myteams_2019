/*
** EPITECH PROJECT, 2020
** client
** File description:
** client
*/

#include "client.h"

int read_server(server_t *client, char *buffer)
{
    int n = 0;

    if ((n = recv(client->fd, buffer, BUF_SIZE - 1, 0)) < 0) {
        perror(BAS_RECV);
        return EXIT_ERROR;
    }
    buffer[n] = 0;
    return n;
}

int write_server(server_t *client, const char *buffer)
{
    FD_ZERO(&client->wrfs);
    FD_SET(STDIN_FILENO, &client->wrfs);
    FD_SET(client->fd, &client->wrfs);
    if (select(client->fd + 1, NULL, &client->wrfs, NULL, NULL) == -1) {
        perror(BAD_SELECT);
        return EXIT_ERROR;
    }
    if (FD_ISSET(client->fd, &client->wrfs)) {
        if (send(client->fd, buffer, strlen(buffer), 0) < 0) {
            perror(BAD_SEND);
            return EXIT_ERROR;
        }
    } else
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int connection(server_t *client)
{
    FD_ZERO(&client->rdfs);
    FD_SET(STDIN_FILENO, &client->rdfs);
    FD_SET(client->fd, &client->rdfs);
    if (select(client->fd + 1, &client->rdfs, NULL, NULL, NULL) == -1) {
        perror(BAD_SELECT);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int managment_client(server_t *client)
{
    char buffer[BUF_SIZE];

    write_server(client, "/ok");
    while (1) {
        if (connection(client) == EXIT_ERROR)
            return EXIT_ERROR;
        if (FD_ISSET(STDIN_FILENO, &client->rdfs)) {
            preparation_message(buffer, client);
        } else if (FD_ISSET(client->fd, &client->rdfs)) {
            if (read_server(client, buffer) == 0) {
                printf("Server disconnected !\n");
                break;
            }
            if (parsing(client, buffer) == EXIT_ERROR)
                break;
        }
    }
    close(client->fd);
    return EXIT_SUCCESS;
}

int client(int ac, char **av)
{
    server_t *client = malloc(sizeof(server_t));

    if (check_len(ac, av) == EXIT_ERROR)
        return EXIT_ERROR;
    if (check_port(av[2]) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_client(av[1], atoi(av[2]), client) == EXIT_ERROR)
        return EXIT_ERROR;
    return (managment_client(client));
}
