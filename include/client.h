/*
** EPITECH PROJECT, 2020
** client
** File description:
** client
*/

#ifndef MY_CLI
#define MY_CLI

#include "include.h"
#include "../libs/myteams/logging_client.h"

typedef struct server_s {
    int fd;
    struct sockaddr_in sockaddr_in_s;
    struct in_addr in_addr_s;
    struct hostent *hostinfo;
    char *prompt;
    char *name;
    fd_set rdfs;
    fd_set wrfs;
    char *id;
    char *team;
    char *channel;
    char *thread;
} server_t;

typedef int (*fptr)(server_t *clients, const char **array);
fptr command[16];

const char **my_str_to_command_tab(char *);
int logout(server_t *, const char **);
int login(server_t *, const char **);
int users(server_t *, const char **);
int user(server_t *, const char **);
int messages(server_t *, const char **);
int subscribe(server_t *, const char **);
int subscribed(server_t *, const char **);
int unsubscrib(server_t *, const char **);
int unauthorized(server_t *, const char **);
int use(server_t *, const char **);
int list(server_t *, const char **);
int create(server_t *, const char **);
int info(server_t *, const char **);
int my_send(server_t *, const char **);
int client(int, char **);
int parsing(server_t *, char *);
int check_port(char *);
int check_len(int, char **);
int help(server_t *, const char **);
int check_int(char *);
int init_client(const char *, int, server_t *);
int preparation_message(char *, server_t *);
int write_server(server_t *, const char *);
void modify_prompt(server_t *);
void display_prompt(server_t *);
char *my_strcat(char *, char const *);
int ok(server_t *, const char **);

#endif // MY_CLI //
