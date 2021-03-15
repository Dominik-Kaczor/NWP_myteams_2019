/*
** EPITECH PROJECT, 2020
** parsing
** File description:
** parsing
*/

#include "client.h"

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
    command[14] = &unauthorized;
    command[15] = &ok;
}

int ok(server_t *clients, const char **array)
{
    (void)clients;
    (void)array;
    return EXIT_SUCCESS;
}

int parsing(server_t *clients, char *buffer)
{
    const char *new_buffer = strdup(buffer);
    const char **buffer_split = my_str_to_command_tab(buffer);
    char *command_list[16] = {"/help", "/login", "/logout", "/users", "/user",
    "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info", "/unauthorized", "/ok"};

    if (buffer_split == NULL) {
        printf("%s\n", new_buffer);
        return EXIT_SUCCESS;
    }
    init_function();
    for (int i = 0; i <= 15; i++) {
        if (strcmp(buffer_split[0], command_list[i]) == 0)
            return ((command[i])(clients, buffer_split));
    }
    return EXIT_SUCCESS;
}
