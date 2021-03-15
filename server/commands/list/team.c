/*
** EPITECH PROJECT, 2020
** team
** File description:
** team
*/

#include "server.h"

void remove_team(char *team)
{
    rmdir(team);
    remove(team);
}

char *add_message_id_des(char *name, char *team, char *msg, FILE *fp)
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

char *list_team_managment(char *msg, char *team, char *name)
{
    char *info = my_strcat(team, "/.info.txt");
    FILE *fp;

    memmove(name, name + 1, strlen(name));
    if (access(info, F_OK) == -1) {
        remove_team(team);
        return msg;
    }
    fp = fopen(info, "r");
    msg = add_message_id_des(name, team, msg, fp);
    fclose(fp);
    return msg;
}

int list_team(client_t client)
{
    DIR *mydir;
    struct dirent *myfile;
    char *msg = "/list ";

    mydir = opendir(".data_base/.teams/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0)
            msg = list_team_managment(msg,
            my_strcat(".data_base/.teams/", myfile->d_name), myfile->d_name);
    }
    if (send_client(client.fd, msg) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}