/*
** EPITECH PROJECT, 2020
** tools
** File description:
** tools
*/

#include "client.h"

static int count_commands(char *str)
{
    int i = 0;
    int count = 0;
    int cote = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ' && cote == 0) {
            count += 1;
            cote = 1;
        }
        else if (str[i] == '"' && cote > 0)
            cote += 1;
        if (cote == 3) {
            count += 1;
            cote = 1;
        }
        i += 1;
    }
    return (count);
}

int stringl(char *str, int pos)
{
    if (str[0] == '\0')
        return (0);
    while ((str[pos] != '\0' && str[pos] != '"')) {
        pos += 1;
    }
    if (str[pos] == '\0')
        return (-1);
    return (0);
}

const char **my_str_to_command_tab(char *str)
{
    int j = 0;
    char **tab = malloc(sizeof(char *) * (count_commands(str) + 1));
    char *token;
    char *rest = str;

    if ((token = strtok_r(rest, " ", &rest)))
        tab[j] = token;
    else
        return (NULL);
    if ((rest[0] != '\"' && rest[0] != '\0') || (stringl(rest, 1) == -1))
        return (NULL);
    while ((token = strtok_r(rest, "\"", &rest))) {
        tab[++j] = token;
        if (rest[0] == ' ')
            rest = rest + 1;
        if ((rest[0] != '\"'  && rest[0] != '\0') || (stringl(rest, 1) == -1))
            return (NULL);
    }
    tab[j + 1] = NULL;
    return (const char **)(tab);
}