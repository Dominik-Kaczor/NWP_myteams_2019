/*
** EPITECH PROJECT, 2020
** team
** File description:
** team
*/

#include "server.h"

int user_sub_too_team_use(client_t *client, char *name, char const *id)
{
    char *file = my_strcat(".data_base/.users/.", client->name);
    FILE *fp = fopen(my_strcat(file, ".txt"), "r");
    char contained[250];
    char *team;
    char *msg = "/use ";

    while (fgets(contained, 250, fp)) {
        team = strtok(contained, "|");
        if (strcmp(team, name) == 0) {
            client->team = strdup(name);
            client->team_id = strdup(id);
            msg = my_strcat(msg, add_quotes(name));
            msg = my_strcat(msg, " ");
            msg = my_strcat(msg, add_quotes((char *)id));
            return send_client(client->fd, msg);
        }
    }
    return send_client(client->fd, "/unauthorized");
}

int cmp_use_team(char *team, char const *id, client_t *client, char *name)
{
    char contained[250];
    char description[250];
    FILE *fp;
    char *info = my_strcat(team, "/.info.txt");

    if (access(info, F_OK) == -1) {
        remove_team(team);
        return EXIT_ERROR;
    }
    fp = fopen(info, "r");
    if (fgets(contained, 250, fp) == NULL ||
    fgets(description, 250, fp) == NULL || strlen(contained) != 37) {
        remove_team(team);
        return EXIT_ERROR;
    }
    if (strcmp(remove_end(contained, 1), id) == 0) {
        memmove(name, name + 1, strlen(name));
        return (user_sub_too_team_use(client, name, id));
    }
    return EXIT_ERROR;
}

int check_user(client_t *client)
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
    return EXIT_ERROR;
}

int use_team(client_t *client, char const *id)
{
    DIR *mydir;
    struct dirent *myfile;
    char *team;

    if (check_user(client) == EXIT_SUCCESS)
        return EXIT_SUCCESS;
    mydir = opendir(".data_base/.teams/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0) {
            team = my_strcat(".data_base/.teams/", myfile->d_name);
            if (cmp_use_team(team, id, client, myfile->d_name) ==
            EXIT_SUCCESS)
                return EXIT_SUCCESS;
        }
    }
    return (send_client(client->fd, my_strcat("/use ",
    add_quotes((char *)id))));
    return EXIT_SUCCESS;
}