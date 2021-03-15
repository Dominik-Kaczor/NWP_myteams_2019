/*
** EPITECH PROJECT, 2020
** user
** File description:
** user
*/

#include "server.h"

char *user_to_message(char *file, char *contained, char const *name,
client_t *clients)
{
    char *infos = "";

    memmove(file, file + 1, strlen(file));
    if (!strcmp(remove_end(contained, 1), name)) {
        infos = my_strcat(infos, add_quotes(remove_end(contained, 1)));
        infos = my_strcat(infos, " ");
        infos = my_strcat(infos, add_quotes(remove_end(file, 4)));
        infos = my_strcat(infos, is_connected(clients, remove_end(file, 4)));
    }
    return infos;
}

char *get_user_ids(char *file, client_t *clients, char const *name)
{
    size_t len = strlen(file) * sizeof(char) + sizeof(".data_base/.users/") + 1;
    char *pfile = malloc(len);
    char contained[250];
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    pfile[len - 1] = '\0';
    fp = fopen(pfile, "r");
    if (fgets(contained, 250, fp) == NULL) {
        remove(pfile);
        return "";
    }
    if (strlen(contained) != 37) {
        remove(pfile);
        return "";
    }
    pfile = user_to_message(file, contained, name, clients);
    fclose(fp);
    return pfile;
}

char *users_infos_user(client_t *clients, char const *name)
{
    DIR *mydir;
    struct dirent *myfile;
    char *infos = "";

    mydir = opendir(".data_base/.users/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") && strcmp(myfile->d_name, ".")) {
            infos = my_strcat(infos,
            get_user_ids(myfile->d_name, clients, name));
        }
    }
    closedir(mydir);
    return infos;
}

int user(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;
    (void)actual;
    char *total = "/user ";

    if (clients[sender].name == NULL) {
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    }
    while (array[counter])
        counter++;
    if (counter != 2)
        return send_client(clients[sender].fd, "XXX Too many arguments");
    total = my_strcat(total, users_infos_user(clients, array[1]));
    send_client(clients[sender].fd, total);
    return EXIT_SUCCESS;
}