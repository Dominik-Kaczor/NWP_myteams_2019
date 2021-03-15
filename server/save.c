/*
** EPITECH PROJECT, 2020
** save
** File description:
** save
*/

#include "server.h"
#include "errno.h"

void check_id(char *file)
{
    size_t len = strlen(file) * 1 + sizeof(".data_base/.users/") + 1;
    char *pfile = malloc(len);
    char contained[250];
    FILE *fp;

    strcpy(pfile, ".data_base/.users/");
    strcat(pfile, file);
    pfile[len - 1] = '\0';
    fp = fopen(pfile, "r");
    if (fgets(contained, 250, fp) == NULL) {
        remove(pfile);
        return;
    }
    if (strlen(contained) != 37) {
        remove(pfile);
        return;
    }
    memmove(file, file + 1, strlen(file));
    server_event_user_loaded(remove_end(contained, 1), remove_end(file, 4));
    fclose(fp);
}

void check_save(void)
{
    DIR *mydir;
    struct dirent *myfile;

    mydir = opendir(".data_base/.users/");
    if (mydir == NULL) {
        check_and_create_folders();
    } else {
        while ((myfile = readdir(mydir)) != NULL) {
            if (strcmp(myfile->d_name, "..") != 0 &&
            strcmp(myfile->d_name, ".") != 0)
                check_id(myfile->d_name);
        }
    }
    closedir(mydir);
}