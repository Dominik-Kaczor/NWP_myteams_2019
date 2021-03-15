/*
** EPITECH PROJECT, 2020
** message
** File description:
** message
*/

#include "server.h"

char **get_all_msgs(void)
{
    char **dest;
    char *l_content = NULL;
    char *content = "";
    size_t line = 1024;
    FILE *fp = fopen(".data_base/.messages/.msg.txt", "r");

    if (fp == NULL)
        return NULL;
    while (getline(&l_content, &line, fp) != -1) {
        content = my_strcat(content, l_content);
    }
    fclose(fp);
    dest = tab_infos(content, '\n');
    return dest;
}

char *pars(char *str, char const *id1, char const *id2)
{
    char **infos = tab_infos(str, '|');
    char *cmd = "";

    if (!strcmp(infos[0], id1) && !strcmp(infos[1], id2)) {
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[0])));
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[2])));
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[3])));
    }
    if (!strcmp(infos[0], id2) && !strcmp(infos[1], id1)) {
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[0])));
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[2])));
        cmd = my_strcat(cmd, my_strcat(" ", add_quotes(infos[3])));
    }
    return cmd;
}

char *get_messages(const char **array, char *id)
{
    char **all_msgs = get_all_msgs();
    char *cmd = "";

    if (all_msgs == NULL)
        return cmd;
    for (int i = 0; all_msgs[i] != NULL; i++) {
        cmd = my_strcat(cmd, pars(all_msgs[i], array[1], id));
    }
    return cmd;
}

int messages(client_t *clients, int sender, const char **array, int actual)
{
    int counter  = 0;
    char *cmd = "/messages";

    while (array[counter++]);
    (void)actual;
    if (clients[sender].name == NULL)
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    if (counter == 3) {
        cmd = my_strcat(cmd, get_messages(array, clients[sender].id));
        send_client(clients[sender].fd, cmd);
    }
    return EXIT_SUCCESS;
}