/*
** EPITECH PROJECT, 2020
** folder
** File description:
** folder
*/

#include "server.h"

int check_and_create_folders(void)
{
    char *folders[] = {".data_base",
                    ".data_base/.users/",
                    ".data_base/.teams/",
                    ".data_base/.messages/", NULL};

    for (int i = 0; folders[i] != NULL; i++) {
        if (check_folder(folders[i]) == EXIT_ERROR) {
            mkdir(folders[i], 0777);
        }
    }
    return EXIT_SUCCESS;
}

int check_folder(char *folder)
{
    struct stat s;
    int err = stat(folder, &s);

    if (err == -1) {
        if (ENOENT == errno) {
            return EXIT_ERROR;
        }
    } else {
        if (S_ISDIR(s.st_mode)) {
            return EXIT_SUCCESS;
        } else {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int check_team_sub(client_t *client, char const *id)
{
    DIR *mydir;
    struct dirent *myfile;
    char *team;

    mydir = opendir(".data_base/.teams/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0) {
            team = my_strcat(".data_base/.teams/", myfile->d_name);
            if (cmp_id_team_sub(team, id, client, myfile->d_name) ==
            EXIT_SUCCESS)
                return EXIT_SUCCESS;
        }
    }
    return (send_client(client->fd, my_strcat("/subscribe ",
    add_quotes((char *)id))));
}

int check_team_unsub(client_t *client, char const *id)
{
    DIR *mydir;
    struct dirent *myfile;
    char *team;

    mydir = opendir(".data_base/.teams/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0) {
            team = my_strcat(".data_base/.teams/", myfile->d_name);
            if (cmp_id_team_unsub(team, id, client, myfile->d_name) ==
            EXIT_SUCCESS)
                return EXIT_SUCCESS;
        }
    }
    return (send_client(client->fd, my_strcat("/unsubscribe ",
    add_quotes((char *)id))));
}