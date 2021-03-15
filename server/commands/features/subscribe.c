/*
** EPITECH PROJECT, 2020
** subsrite
** File description:
** sub
*/

#include "server.h"

int add_user_too_team(client_t *client, char *name, char *file, char const *id)
{
    FILE *fp = fopen(file, "a");
    char *msg = "/subscribe ";

    fprintf(fp, "%s", name);
    fclose(fp);
    msg = my_strcat(msg, add_quotes(client->id));
    msg = my_strcat(msg, " ");
    msg = my_strcat(msg, add_quotes((char *)id));
    server_event_user_join_a_team(id, client->id);
    return send_client(client->fd, msg);
}

int user_id_team_sub(client_t *client, char *name, char const *id,
char *description)
{
    char *file = ".data_base/.users/.";
    char contained[250];
    FILE *fp;

    file = my_strcat(file, client->name);
    file = my_strcat(file, ".txt");
    fp = fopen(file, "r");
    memmove(name, name + 1, strlen(name));
    while (fgets(contained, 250, fp)) {
        if (strcmp(remove_end(contained, 1), name) == 0)
            return (send_client(client->fd, "/subscribe"));
    }
    fclose(fp);
    name = my_strcat(name, "|");
    name = my_strcat(name, client->id);
    name = my_strcat(name, "|");
    name = my_strcat(name, description);
    return add_user_too_team(client, name, file, id);
}

int cmp_id_team_sub(char *team, char const *id, client_t *client, char *name)
{
    char contained[250];
    char description[250];
    FILE *fp;
    char *info = my_strcat(team, "/.info.txt");

    if (access(info, F_OK) == -1) {
        remove_team(team);
        return EXIT_ERROR;
    }
    fp = fopen(info, "r");
    if (fgets(contained, 250, fp) == NULL ||
    fgets(description, 250, fp) == NULL || strlen(contained) != 37) {
        remove_team(team);
        return EXIT_ERROR;
    }
    if (strcmp(remove_end(contained, 1), id) == 0)
        return (user_id_team_sub(client, name, id, description));
    return EXIT_ERROR;
}

int check_user_sub(client_t *client, char const *id)
{
    char *file = ".data_base/.users/.";
    char contained[250];
    FILE *fp;

    file = my_strcat(file, client->name);
    file = my_strcat(file, ".txt");
    if (access(file, F_OK) == -1) {
        client->name = NULL;
        client->id = NULL;
        return send_client(client->fd, "/unauthorized");
    }
    fp = fopen(file, "r");
    if (fgets(contained, 250, fp) == NULL || strlen(contained) != 37) {
        client->name = NULL;
        client->id = NULL;
        remove(file);
        return send_client(client->fd, "/unauthorized");
    }
    fclose(fp);
    return check_team_sub(client, id);
}

int subscribe(client_t *clients, int sender, const char **array, int actual)
{
    int counter = 0;

    (void)actual;
    while (array[counter])
        counter++;
    if (clients[sender].name == NULL)
        if (send_client(clients[sender].fd, "/unauthorized") == EXIT_ERROR)
            return EXIT_ERROR;
    if (counter != 2)
        return (send_client(clients[sender].fd, "XXX Too many arguments"));
    return check_user_sub(&clients[sender], array[1]);
}