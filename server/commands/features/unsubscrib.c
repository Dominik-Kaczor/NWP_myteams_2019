/*
** EPITECH PROJECT, 2020
** unsubscrib
** File description:
** unsubscrib
*/

#include "server.h"

int remove_user_too_team(client_t *client, char *name, char *file,
char const *id)
{
    FILE *fp = fopen(file, "r");
    FILE *tmp = fopen("tmp.txt", "w");
    char *msg = "/unsubscribe ";
    char contained[250];

    while (fgets(contained, 250, fp)) {
        if (strcmp(remove_end(contained, 1), name) != 0)
            fprintf(tmp, "%s\n", contained);
    }
    fclose(fp);
    fclose(tmp);
    msg = my_strcat(msg, add_quotes(client->id));
    msg = my_strcat(msg, " ");
    msg = my_strcat(msg, add_quotes((char *)id));
    remove(file);
    rename("tmp.txt", file);
    return send_client(client->fd, msg);
}

int user_id_team_unsub(client_t *client, char *name, char const *id)
{
    char *file = ".data_base/.users/.";
    char contained[250];
    FILE *fp;

    file = my_strcat(file, client->name);
    file = my_strcat(file, ".txt");
    fp = fopen(file, "r");
    memmove(name, name + 1, strlen(name));
    while (fgets(contained, 250, fp)) {
        if (strcmp(remove_end(contained, 1), name) == 0) {
            fclose(fp);
            server_event_user_leave_a_team(id, client->id);
            return remove_user_too_team(client, name, file, id);
        }
    }
    fclose(fp);
    return (send_client(client->fd, "/unsubscribe"));
}

int cmp_id_team_unsub(char *team, char const *id, client_t *client, char *name)
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
    fgets(description, 250, fp) == NULL ||
    strlen(contained) != 37) {
        remove_team(team);
        return EXIT_ERROR;
    }
    if (strcmp(remove_end(contained, 1), id) == 0)
        return (user_id_team_unsub(client, name, id));
    return EXIT_ERROR;
}

int check_user_unsub(client_t *client, char const *id)
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
    return check_team_unsub(client, id);
}

int unsubscrib(client_t *clients, int sender, const char **array, int actual)
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
    return check_user_unsub(&clients[sender], array[1]);
}