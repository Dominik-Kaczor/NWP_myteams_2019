/*
** EPITECH PROJECT, 2020
** team
** File description:
** team
*/

#include "server.h"

int message_one_create(client_t *clients, int sender, info_t *info)
{
    char *message = "/create ";

    message = my_strcat(message, add_quotes(info->info_1));
    message = my_strcat(message, " ");
    message = my_strcat(message, add_quotes(info->info_2));
    message = my_strcat(message, " ");
    message = my_strcat(message, add_quotes(info->info_3));
    message = my_strcat(message, " \"team\" \"OK\"");
    if (send_client(clients[sender].fd, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int message_all_create(client_t *clients, int sender, int actual, info_t *info)
{
    char *message = "/create ";

    message = my_strcat(message, add_quotes(info->info_1));
    message = my_strcat(message, " ");
    message = my_strcat(message, add_quotes(info->info_2));
    message = my_strcat(message, " ");
    message = my_strcat(message, add_quotes(info->info_3));
    message = my_strcat(message, " \"team\"");
    if (send_choose_clients(clients, sender, actual, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int init_new_team(client_t *clients, int sender, int actual, info_t *info)
{
    uuid_t binuuid;
    size_t len = strlen(info->info_4) + 1 + sizeof(".info.txt");
    char *finfo = malloc(len);
    char new[37];

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, new);
    info->info_2 = strdup(new);
    mkdir(info->info_4, 0777);
    strcpy(finfo, info->info_4);
    strcat(finfo, ".info.txt");
    finfo[len - 1] = '\0';
    add_file_info(finfo, new, info->info_3);
    server_event_team_created(new, info->info_1, clients[sender].id);
    if (message_one_create(clients, sender, info) == EXIT_ERROR)
        return EXIT_ERROR;
    if (message_all_create(clients, sender, actual, info) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int team_managment(client_t *clients, int sender, const char **array,
int actual)
{
    size_t len = sizeof(".data_base/.teams/.") + 2 + strlen(array[1]);
    char *folder = malloc(len);
    info_t *info = malloc(sizeof(info_t));

    strcpy(folder, ".data_base/.teams/.");
    strcat(folder, array[1]);
    strcat(folder, "/");
    folder[len - 1] = '\0';
    if (check_folder(folder) == EXIT_ERROR) {
        info->info_1 = strdup(array[1]);
        info->info_3 = strdup(array[2]);
        info->info_4 = strdup(folder);
        if (init_new_team(clients, sender, actual, info) == EXIT_ERROR)
            return EXIT_ERROR;
        return EXIT_SUCCESS;
    }
    if (send_client(clients[sender].fd, "/create") == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}