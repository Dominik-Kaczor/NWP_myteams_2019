/*
** EPITECH PROJECT, 2020
** initialisation
** File description:
** initialisation
*/

#include "client.h"

void init_infos(server_t *client)
{
    client->prompt = "";
    client->name = NULL;
    client->id = NULL;
    client->team = NULL;
    client->channel = NULL;
    client->thread = NULL;
    FD_ZERO(&client->rdfs);
    FD_SET(STDIN_FILENO, &client->rdfs);
    FD_SET(client->fd, &client->rdfs);
    FD_ZERO(&client->wrfs);
    FD_SET(STDIN_FILENO, &client->wrfs);
    FD_SET(client->fd, &client->wrfs);
}

int init_socket(const char *address, server_t *client)
{
    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd == INVALID_SOCKET) {
        perror(BAD_SOCKET);
        return EXIT_ERROR;
    }
    client->hostinfo = gethostbyname(address);
    if (client->hostinfo == NULL) {
        perror(BAD_HOSTINFO);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int init_client(const char *address, int port, server_t *client)
{
    if (init_socket(address, client) == EXIT_ERROR)
        return EXIT_ERROR;
    client->sockaddr_in_s.sin_addr =
    *(struct in_addr *)client->hostinfo->h_addr_list[0];
    client->sockaddr_in_s.sin_port = htons(port);
    client->sockaddr_in_s.sin_family = AF_INET;
    if (connect(client->fd, (struct sockaddr *) &client->sockaddr_in_s,
    sizeof(client->sockaddr_in_s)) == SOCKET_ERROR) {
        perror(BAD_CONNECT);
        return EXIT_ERROR;
    }
    init_infos(client);
    return EXIT_SUCCESS;
}