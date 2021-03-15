/*
** EPITECH PROJECT, 2020
** clear
** File description:
** clear
*/

#include "server.h"

void clear_clients(client_t *clients, int actual)
{
    for (int i = 0; i < actual; i++) {
        close(clients[i].fd);
    }
}

void remove_client(client_t *clients, int to_remove, server_t *server)
{
    memmove(clients + to_remove, clients + to_remove + 1,
    (server->nb_client - to_remove - 1) * sizeof(client_t));
    clients[server->nb_client - 1].prompt = "";
    clients[server->nb_client - 1].name = NULL;
    clients[server->nb_client - 1].id = NULL;
    clients[server->nb_client - 1].team = NULL;
    clients[server->nb_client - 1].team_id = NULL;
    clients[server->nb_client - 1].channel = NULL;
    clients[server->nb_client - 1].channel_id = NULL;
    clients[server->nb_client - 1].thread = NULL;
    clients[server->nb_client - 1].thread_id = NULL;
    server->nb_client--;
}