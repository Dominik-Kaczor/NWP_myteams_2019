/*
** EPITECH PROJECT, 2020
** parsing
** File description:
** parsing
*/

#include "server.h"

void init_function(void)
{
    command[0] = &help;
    command[1] = &login;
    command[2] = &logout;
    command[3] = &users;
    command[4] = &user;
    command[5] = &my_send;
    command[6] = &messages;
    command[7] = &subscribe;
    command[8] = &subscribed;
    command[9] = &unsubscrib;
    command[10] = &use;
    command[11] = &create;
    command[12] = &list;
    command[13] = &info;
    command[14] = &ok;
}

int ok(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;
    (void)actual;

    while (array[counter])
        counter++;
    if (counter != 1)
        if (send_client(clients[sender].fd, "XXX Command not found")
        == EXIT_ERROR)
            return EXIT_ERROR;
    if (send_client(clients[sender].fd, "/ok") == EXIT_ERROR)
            return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int parsing(client_t *clients, int sender, char *buffer, int nb_client)
{
    const char **buffer_split = my_str_to_command_tab(buffer);
    char *command_list[15] = {"/help", "/login", "/logout", "/users", "/user",
    "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info", "/ok"};

    if (buffer_split == NULL) {
        if (send_client(clients[sender].fd, "XXX Bad Buffer") == EXIT_ERROR)
            return EXIT_ERROR;
        return EXIT_SUCCESS;
    }
    check_and_create_folders();
    init_function();
    for (int i = 0; i <= 14; i++) {
        if (strcmp(buffer_split[0], command_list[i]) == 0)
            return ((command[i])(clients, sender, buffer_split, nb_client));
    }
    if (send_client(clients[sender].fd, "XXX Command not found") == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
