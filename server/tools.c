/*
** EPITECH PROJECT, 2020
** tools
** File description:
** tools
*/

#include "server.h"

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
        printf("%s", HELP_SERVER);
        return EXIT_ERROR;
    } else if (ac == 2) {
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

char *remove_end(char *str, int nb)
{
    int len = strlen(str);

    str[len - nb] = '\0';
    return str;
}

char *add_quotes(const char *str)
{
    char *dump = malloc(sizeof(char) * (strlen(str) + 3));
    int i = 0;

    dump[0] = '\"';
    while (str[i]) {
        dump[i + 1] = str[i];
        i++;
    }
    dump[i + 1] = '\"';
    dump[i + 2] = '\0';
    return dump;
}
