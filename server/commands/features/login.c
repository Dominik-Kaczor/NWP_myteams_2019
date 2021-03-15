/*
** EPITECH PROJECT, 2020
** login
** File description:
** login
*/

#include "server.h"

int message_one_login(client_t *clients, int sender)
{
    size_t len = sizeof(char) * 55 + sizeof(clients[sender].name);
    char *message = malloc(len);

    strcpy(message, "/login ");
    strcat(message, add_quotes(clients[sender].name));
    strcat(message, " ");
    strcat(message, add_quotes(clients[sender].id));
    strcat(message, " \"OK\"");
    message[len - 1] = '\0';
    if (send_client(clients[sender].fd, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int message_all_login(client_t *clients, int sender, int actual)
{
    size_t len = sizeof(char) * 50 + sizeof(clients[sender].name);
    char *message = malloc(len);

    strcpy(message, "/login ");
    strcat(message, add_quotes(clients[sender].name));
    strcat(message, " ");
    strcat(message, add_quotes(clients[sender].id));
    message[len - 1] = '\0';
    if (send_choose_clients(clients, sender, actual, message) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int check_connection(client_t *clients, int actual, const char *name)
{
    for (int i = 0; i < actual; i++) {
        if (clients[i].name == NULL)
            continue;
        else if (strcmp(clients[i].name, name) == 0)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

void login_assignation(client_t *clients, int sender, const char *name)
{
    uuid_t binuuid;
    char new[37];
    char *file = malloc(sizeof(name) + 6);

    strcpy(file, ".");
    strcat(file, name);
    strcat(file, ".txt");
    file[sizeof(name) + 5] = '\0';
    if (get_file_user_info(&clients[sender], file) == EXIT_ERROR) {
        clients[sender].name = strdup(name);
        return;
    }
    clients[sender].name = strdup(name);
    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, new);
    clients[sender].id = strdup(new);
    add_file_user_info(clients[sender], file);
    server_event_user_created(clients[sender].id, clients[sender].name);
}

int login(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    if (clients[sender].name != NULL)
        return (send_client(clients[sender].fd,
        "XXX For change please loggout"));
    while (array[counter])
        counter++;
    if (counter != 2)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    if (strlen(array[1]) > MAX_NAME_LENGTH)
        return (send_client(clients[sender].fd, "XXX Name is too long"));
    login_assignation(clients, sender, array[1]);
    server_event_user_logged_in(clients[sender].id);
    if (message_one_login(clients, sender) == EXIT_ERROR)
        return EXIT_ERROR;
    if (message_all_login(clients, sender, actual) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}