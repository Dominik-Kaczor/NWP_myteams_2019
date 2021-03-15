/*
** EPITECH PROJECT, 2020
** prompt
** File description:
** prompt
*/

#include "client.h"

void display_prompt(server_t *client)
{
    printf("%s", client->prompt);
}

void modify_prompt(server_t * client)
{
    char *new = "";

    new = my_strcat(new, client->name);
    if (client->team != NULL) {
        new = my_strcat(new, "/");
        new = my_strcat(new, client->team);
    }
    if (client->channel != NULL) {
        new = my_strcat(new, "/");
        new = my_strcat(new, client->channel);
    }
    if (client->thread != NULL) {
        new = my_strcat(new, "/");
        new = my_strcat(new, client->thread);
    }
    new = my_strcat(new, "> ");
    client->prompt = new;
}
