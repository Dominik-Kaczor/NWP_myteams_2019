/*
** EPITECH PROJECT, 2020
** select
** File description:
** select
*/

#include "server.h"

int managment_select(int max, server_t *server, client_t *clients)
{
    FD_ZERO(&server->rdfs);
    FD_SET(STDIN_FILENO, &server->rdfs);
    FD_SET(server->fd, &server->rdfs);
    for (int i = 0; i < server->nb_client; i++) {
        FD_SET(clients[i].fd, &server->rdfs);
    }
    if (select(max + 1, &server->rdfs, NULL, NULL, NULL) == -1) {
        perror(BAD_SELECT);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
