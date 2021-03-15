/*
** EPITECH PROJECT, 2020
** user
** File description:
** user
*/

#include "server.h"

int message_info_user(client_t *client, char *contained)
{
    char *msg = "/info ";

    client->id = strdup(remove_end(contained, 1));
    msg = my_strcat(msg, add_quotes(client->id));
    msg = my_strcat(msg, " ");
    msg = my_strcat(msg, add_quotes(client->name));
    msg = my_strcat(msg, " \"1\"");
    return send_client(client->fd, msg);
}

int info_user(client_t *client)
{
    char *file = ".data_base/.users/.";
    char contained[250];
    FILE *fp;

    file = my_strcat(file, client->name);
    file = my_strcat(file, ".txt");
    if (access(file, F_OK) == -1) {
        client->name = NULL;
        client->id = NULL;
        return send_client(client->fd, "/unauthorized");
    }
    fp = fopen(file, "r");
    if (fgets(contained, 250, fp) == NULL || strlen(contained) != 37) {
        client->name = NULL;
        client->id = NULL;
        remove(file);
        return send_client(client->fd, "/unauthorized");
    }
    fclose(fp);
    return message_info_user(client, contained);
}