/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#include "server.h"

void intHandler(int dummy)
{
    (void)dummy;
    keepRunning = 0;
}

int first_connection(int max, server_t *server, client_t *clients)
{
    char buffer[BUF_SIZE];
    struct sockaddr_in csin = { 0 };
    size_t sinsize = sizeof(csin);
    int csock = accept(server->fd, (struct sockaddr *)&csin,
    (socklen_t *)&sinsize);

    if (csock == SOCKET_ERROR) {
        perror(BAD_ACCEPT);
        return max;
    }
    if (read_client(csock, buffer) == -1)
        return max;
    if (csock > max)
        max = csock;
    FD_SET(csock, &server->rdfs);
    clients[server->nb_client].fd = csock;
    parsing(clients, server->nb_client, buffer, server->nb_client);
    server->nb_client++;
    return max;
}

void connection(server_t *server, client_t *clients)
{
    char buffer[BUF_SIZE];
    int info = 0;

    for (int i = 0; i < server->nb_client; i++) {
        if (FD_ISSET(clients[i].fd, &server->rdfs)) {
            info = read_client(clients[i].fd, buffer);
            if (info == 0) {
                close(clients[i].fd);
                remove_client(clients, i, server);
            } else
                parsing(clients, i, buffer, server->nb_client);
            break;
        }
    }
}

int managment_serveur(server_t *server, client_t *clients)
{
    int max = server->fd;

    signal(SIGINT, intHandler);
    check_save();
    while (keepRunning != 0) {
        managment_select(max, server, clients);
        if (FD_ISSET(STDIN_FILENO, &server->rdfs))
            break;
        else if (FD_ISSET(server->fd, &server->rdfs))
            max = first_connection(max, server, clients);
        else
            connection(server, clients);
    }
    clear_clients(clients, server->nb_client);
    close(server->fd);
    return EXIT_SUCCESS;
}

int server(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    client_t clients[MAX_CLIENT_IN_SERVER];

    if (check_len(ac, av) == EXIT_ERROR)
        return EXIT_ERROR;
    if (check_port(av[1]) == EXIT_ERROR)
        return EXIT_ERROR;
    if (init_server(atoi(av[1]), server) == EXIT_ERROR)
        return EXIT_ERROR;
    init_client(clients, server);
    check_and_create_folders();
    return managment_serveur(server, clients);
}