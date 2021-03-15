/*
** EPITECH PROJECT, 2020
** help
** File description:
** help
*/

#include "server.h"

char *get_help(void)
{
    return ("/help "\
    "\"/help: show help\n"\
    "/login [username]: set the username used by client\n"\
    "/logout: disconnect the client from the server\n"\
    "/users: get the list of all users that exists on the domain\n"\
    "/user [user_uuid]: get information about user\n"\
    "/send [user_uuid][message_body]: send a message to a user\n"\
    "/messages [user_uuid]: list all messages exchange with a user\n"\
    "/subscribe [team_uuid]: subscribe to the event of a team and its sub "\
    "directories (enable reception of all events from a team)\n"\
    "/subscribed ?[team_uuid]: list all subscrided teams or list all users"\
    " subscribed to team\n"\
    "/unsubscribe [team_uuid]: unsubscribe froma a team\n"\
    "/use ?[team_uuid]?[channel_uuid]?[thread_uuid]: use specify a"\
    " context team/channel/thread\n"\
    "/create: based on what is being used creat the sub resource"\
    " (see below)\n"\
    "/list: based on what is being used list all the sub resources"\
    " (see below)\n"\
    "/info: based on what is being used list the current (see below)\n\"");
}

int help(client_t *clients, int sender, const char **array, int actual)
{
    (void)array;
    (void)actual;
    if (clients[sender].name == NULL) {
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    }  else {
        if (send_client(clients[sender].fd, get_help()) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
