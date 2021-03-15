/*
** EPITECH PROJECT, 2020
** file
** File description:
** file
*/

#include "server.h"

char *get_file_id(char *file)
{
    char contained[250];
    FILE *fp;

    fp = fopen(file, "r");
    if (fgets(contained, 250, fp) == NULL) {
        fclose(fp);
        return EXIT_SUCCESS;
    }
    fclose(fp);
    return remove_end(contained, 1);
}

void add_file_info(char *file, char *id, char *description)
{
    FILE *fp;

    fp = fopen(file, "w");
    fprintf(fp, "%s\n%s\n", id, description);
    fclose(fp);
}

void add_file_user_info(client_t client, char *file)
{
    char *pfile = malloc(sizeof(file) + sizeof(".data_base/.users/") + 1);
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    fp = fopen(pfile, "w");
    fprintf(fp, "%s\n", client.id);
    fclose(fp);
}

int get_file_user_info(client_t *client, char *file)
{
    char *pfile = malloc(sizeof(file) + sizeof(".data_base/.users/") + 2);
    char contained[250];
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    if (access(pfile, F_OK) == -1)
        return EXIT_SUCCESS;
    fp = fopen(pfile, "r");
    if (fgets(contained, 250, fp) == NULL) {
        fclose(fp);
        return EXIT_SUCCESS;
    }
    client->id = strdup(remove_end(contained, 1));
    fclose(fp);
    return EXIT_ERROR;
}