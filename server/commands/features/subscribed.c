/*
** EPITECH PROJECT, 2020
** subscribed
** File description:
** subscribed
*/

#include "server.h"

char *the_team_info(char *contained)
{
    char **tab = tab_infos(contained, '|');
    char *final = "";

    tab[2][strlen(tab[2]) - 1] = '\0';
    for (int i = 0; i < 3; i++) {
        final = my_strcat(final, add_quotes(tab[i]));
        final = my_strcat(final, " ");
    }
    return (final);
}

char *get_user_teams(char *file, char const *name)
{
    size_t len = strlen(file) * sizeof(char) +
    sizeof(".data_base/.users/") + 1;
    size_t line = 1024;
    char *pfile = malloc(len);
    char *contained = NULL;
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    if (strcmp(remove_end(++file, 4), name))
        return "";
    pfile[len - 1] = '\0';
    fp = fopen(pfile, "r");
    getline(&contained, &line, fp);
    pfile = " ";
    while (getline(&contained, &line, fp) != -1) {
        pfile = my_strcat(pfile, the_team_info(contained));
    }
    fclose(fp);
    return pfile;
}

char *list_teams(const char *name)
{
    DIR *mydir;
    struct dirent *myfile;
    char *infos = "";

    mydir = opendir(".data_base/.users/");
    while ((myfile = readdir(mydir)) != NULL) {
        if (strcmp(myfile->d_name, "..") && strcmp(myfile->d_name, ".")) {
            infos = my_strcat(infos,
            get_user_teams(myfile->d_name, name));
        }
    }
    closedir(mydir);
    return infos;
}

int subscribed(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;
    char *cmd = "/subscribed";

    while (array[counter++]);
    (void)actual;
    if (clients[sender].name == NULL)
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    if (counter == 2) {
        cmd = my_strcat(cmd, list_teams(clients[sender].name));
        send_client(clients[sender].fd, cmd);
    }
    return EXIT_SUCCESS;
}