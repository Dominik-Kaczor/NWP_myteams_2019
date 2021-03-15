/*
** EPITECH PROJECT, 2020
** tools
** File description:
** tools
*/

#include "client.h"

int check_int(char *nb)
{
    for (int i = 0; nb[i]; i++) {
        if (nb[i] < '0' || nb[i] > '9')
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int check_len(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("%s", HELP_CLIENT);
        return EXIT_ERROR;
    } else if (ac == 3) {
        return EXIT_SUCCESS;
    } else {
        printf("%s", BAD_ARGUMENTS);
        return EXIT_ERROR;
    }
}

int check_port(char *port_s)
{
    int port_i;

    if (check_int(port_s) == EXIT_ERROR) {
        printf("%s", PORT_NOT_NUMBER);
        return EXIT_ERROR;
    }
    port_i = atoi(port_s);
    if (port_i < 1 || port_i > 65535) {
        printf("%s", PORT_INVALIDE);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int preparation_message(char *buffer, server_t *client)
{
    char *p = NULL;

    fgets(buffer, BUF_SIZE - 1, stdin);
    FD_CLR(STDIN_FILENO, &client->rdfs);
    FD_SET(STDIN_FILENO, &client->rdfs);
    p = strstr(buffer, "\n");
    if (p != NULL)
        *p = 0;
    else
        buffer[BUF_SIZE - 1] = 0;
    if (write_server(client, buffer) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

char *my_strcat(char *one, char const *two)
{
    char *final = malloc(sizeof(char) * (strlen(one) + strlen(two) + 1));
    int i = 0;
    int k = 0;

    for (; one[i]; i++)
        final[i] = one[i];
    while (two[k]) {
        final[i] = two[k];
        i++;
        k++;
    }
    final[i] = '\0';
    return (final);
}