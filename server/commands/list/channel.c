/*
** EPITECH PROJECT, 2020
** channel
** File description:
** channel
*/

#include "server.h"

char *add_message_channel_id_des(char *name, char *team, char *msg, FILE *fp)
{
    char des[250];
    char id[250];

    if (fgets(id, 250, fp) == NULL || strlen(id) != 37)
        remove_team(team);
    else {
        if (fgets(des, 250, fp) == NULL)
            remove_team(team);
        else {
            msg = my_strcat(msg, add_quotes(remove_end(id, 1)));
            msg = my_strcat(msg, " ");
            msg = my_strcat(msg, add_quotes(name));
            msg = my_strcat(msg, " ");
            msg = my_strcat(msg, add_quotes(remove_end(des, 1)));
        }
    }
    return msg;
}

char *list_channel_managment(char *msg, char *team, char *name)
{
    char *info = my_strcat(team, "/.info.txt");
    FILE *fp;

    memmove(name, name + 1, strlen(name));
    if (access(info, F_OK) == -1) {
        remove_team(team);
        return msg;
    }
    fp = fopen(info, "r");
    msg = add_message_channel_id_des(name, team, msg, fp);
    fclose(fp);
    return msg;
}

int list_channel(client_t *client)
{
    DIR *mydir;
    struct dirent *myfile;
    char *msg = "/list ";
    char *dir = ".data_base/.teams/.";

    dir = my_strcat(dir, client->team);
    dir = my_strcat(dir, "/");
    mydir = opendir(dir);
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0 &&
        strcmp(myfile->d_name, ".info.txt") != 0)
            msg = list_channel_managment(msg,
            my_strcat(dir, myfile->d_name), myfile->d_name);
    }
    if (send_client(client->fd, msg) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}