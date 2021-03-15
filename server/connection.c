/*
** EPITECH PROJECT, 2020
** connection
** File description:
** connection
*/

#include "server.h"

int init_bind(server_t *server)
{
    if (bind(server->fd, (struct sockaddr *)&server->sockaddr_in_s,
    sizeof(server->sockaddr_in_s)) == SOCKET_ERROR) {
        perror(BAD_BIND);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int init_listen(server_t *server)
{
    if (listen(server->fd, MAX_CLIENT_IN_SERVER) == SOCKET_ERROR) {
        perror(BAD_LISTEN);
        return (EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

int init_socked(int port, server_t *server)
{
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (server->fd == INVALID_SOCKET) {
        perror(BAD_SOCKET);
        return EXIT_ERROR;
    }
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt))) {
        perror(BAD_SETSOCKOPT);
        return EXIT_ERROR;
    }
    server->sockaddr_in_s.sin_addr.s_addr = htonl(INADDR_ANY);
    server->sockaddr_in_s.sin_port = htons(port);
    server->sockaddr_in_s.sin_family = AF_INET;
    return EXIT_SUCCESS;
}

int init_server(int port, server_t *server)
{
    if (init_socked(port, server) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_bind(server) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_listen(server) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

void init_client(client_t *client, server_t *server)
{
    server->nb_client = 0;
    for (int i = 0; i < MAX_CLIENT_IN_SERVER; i++) {
        client[i].fd = 0;
        client[i].prompt = "";
        client[i].name = NULL;
        client[i].team = NULL;
        client[i].team_id = NULL;
        client[i].channel = NULL;
        client[i].channel_id = NULL;
        client[i].thread = NULL;
        client[i].thread_id = NULL;
        client[i].id = NULL;
    }
    return;
}