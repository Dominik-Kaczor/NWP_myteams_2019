/*
** EPITECH PROJECT, 2020
** team
** File description:
** team
*/

#include "server.h"

int message_info_team(client_t *client, char *contained)
{
    char *msg = "/info ";

    msg = my_strcat(msg, add_quotes(client->team_id));
    msg = my_strcat(msg, " ");
    msg = my_strcat(msg, add_quotes(client->team));
    msg = my_strcat(msg, " ");
    msg = my_strcat(msg, add_quotes(remove_end(contained, 1)));
    return send_client(client->fd, msg);
}

int info_team(client_t *client)
{
    char *file = ".data_base/.teams/.";
    char contained[250];
    FILE *fp;

    file = my_strcat(file, client->team);
    file = my_strcat(file, "/.info.txt");
    if (access(file, F_OK) == -1)
        return send_client(client->fd, "/info");
    fp = fopen(file, "r");
    if (fgets(contained, 250, fp) == NULL || strlen(contained) != 37
    || fgets(contained, 250, fp) == NULL) {
        remove(file);
        return send_client(client->fd, "/info");
    }
    fclose(fp);
    return message_info_team(client, contained);
}