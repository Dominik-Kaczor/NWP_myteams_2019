/*
** EPITECH PROJECT, 2020
** users
** File description:
** users
*/

#include "server.h"

char *is_connected(client_t *clients, char *name)
{
    for (int i = 0; clients[i].fd != 0; i++) {
        if (clients[i].name == NULL)
            return (" \"0\"");
        if (!strcmp(clients[i].name, name))
            return (" \"1\"");
    }
    return (" \"0\"");
}

char *users_message_ids(char *file, char *contained, client_t * clients,
int mode)
{
    char *infos = "";

    memmove(file, file + 1, strlen(file));
    if (mode == 0) {
        infos = my_strcat(infos, add_quotes(remove_end(contained, 1)));
        infos = my_strcat(infos, " ");
        infos = my_strcat(infos, add_quotes(remove_end(file, 4)));
        infos = my_strcat(infos, is_connected(clients, file));
    } else  {
        infos = my_strcat(infos, remove_end(contained, 1));
        infos = my_strcat(infos, " ");
    }
    return infos;
}

char *get_ids(char *file, client_t *clients, int mode)
{
    size_t len = strlen(file) * 1 + sizeof(".data_base/.users/") + 1;
    char *pfile = malloc(len);
    char contained[250];
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    pfile[len - 1] = '\0';
    fp = fopen(pfile, "r");
    if (fgets(contained, 250, fp) == NULL || strlen(contained) != 37) {
        remove(pfile);
        return "";
    }
    pfile = users_message_ids(file, contained, clients, mode);
    fclose(fp);
    return pfile;
}

char *users_infos(client_t *clients, int mode)
{
    DIR *mydir;
    struct dirent *myfile;
    char *infos = "";

    mydir = opendir(".data_base/.users/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") != 0 &&
        strcmp(myfile->d_name, ".") != 0) {
            infos = my_strcat(infos, " ");
            infos = my_strcat(infos, get_ids(myfile->d_name, clients, mode));
        }
    }
    closedir(mydir);
    return infos;
}

int users(client_t *clients, int sender, const char **array, int actual)
{
    (void)actual;
    size_t len = sizeof(char) * 55 + sizeof(clients[sender].name);
    char *message = malloc(len);

    strcpy(message, "/users");
    if (clients[sender].name == NULL) {
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    } else if (array[1] != NULL) {
        if (send_client(clients[sender].fd, "XXX Too many arguments") ==
        EXIT_ERROR)
            return EXIT_ERROR;
    } else {
        message = my_strcat(message, users_infos(clients, 0));
    }
    send_client(clients[sender].fd, message);
    return EXIT_SUCCESS;
}
