/*
** EPITECH PROJECT, 2020
** server
** File description:
** server
*/

#ifndef MY_SER
#define MY_SER

#include "include.h"
#include "../libs/myteams/logging_server.h"

typedef struct info_s {
    char *info_1;
    char *info_2;
    char *info_3;
    char *info_4;
}info_t;

typedef struct client_s {
    int fd;
    char *prompt;
    char *name;
    char *id;
    char *team;
    char *team_id;
    char *channel;
    char *channel_id;
    char *thread;
    char *thread_id;
} client_t;

typedef struct server_s {
    int fd;
    fd_set rdfs;
    fd_set wrfs;
    struct sockaddr_in sockaddr_in_s;
    struct in_addr in_addr_s;
    int nb_client;
} server_t;

typedef int (*fptr)(client_t *clients, int,
const char **array, int actual);
fptr command[15];
static volatile int keepRunning = 1;

int check_and_create_folders(void);
int check_folder(char *);
int server(int, char **);
char *users_infos(client_t *, int);
int check_port(char *);
char *my_strcat(char *, char const *);
void message_file(client_t *, int, const char **);
int send_client(int, const char *);
int check_len(int, char **);
int check_int(char *);
int init_server(int, server_t *);
void init_client(client_t *, server_t *);
int get_char(char *, char);
char **tab_infos(char *, char);
int init_server(int, server_t *);
char **get_list_array(client_t *);
int parsing(client_t *, int, char *, int);
int read_client(int, char *);
int send_client(int, const char *);
char *is_connected(client_t *, char *name);
void remove_client(client_t *, int, server_t *);
void clear_clients(client_t *, int);
int send_all_clients(client_t *, int,  const char *);
int help(client_t *, int, const char **, int);
int login(client_t *, int, const char **, int);
int logout(client_t *, int, const char **, int);
int users(client_t *, int, const char **, int);
int user(client_t *, int, const char **, int);
int my_send(client_t *, int, const char **, int);
int messages(client_t *, int, const char **, int);
int subscribe(client_t *, int, const char **, int);
int subscribed(client_t *, int, const char **, int);
int unsubscrib(client_t *, int, const char **, int);
int use(client_t *, int, const char **, int);
int create(client_t *, int, const char **, int);
int list(client_t *, int, const char **, int);
int info(client_t *, int, const char **, int);
int ok(client_t *, int, const char **, int);
int get_file_user_info(client_t *, char *);
void add_file_user_info(client_t, char *);
int send_choose_clients(client_t *, int, int, const char *);
char *add_quotes(const char *);
const char **my_str_to_command_tab(char *);
char *remove_end(char *, int);
void check_save(void);
int team_managment(client_t *, int, const char **, int);
int channel_managment(client_t *, int, const char **, int);
int thread_managment(client_t *, int, const char **, int);
void add_file_info(char *, char *, char *);
char *get_file_id(char *);
int list_team(client_t);
int list_channel(client_t *);
int list_thread(client_t *);
int list_replie(client_t *);
char *my_strcat(char *, char const *);
void intHandler(int);
int managment_select(int, server_t *, client_t *);
int info_user(client_t *);
int info_team(client_t *);
int info_thread(client_t *);
int info_channel(client_t *);
void remove_team(char *);
int check_team_sub(client_t *, char const *);
int check_team_unsub(client_t *, char const *);
int cmp_id_team_sub(char *, char const *, client_t *, char *);
int cmp_id_team_unsub(char *, char const *, client_t *, char *);
int use_team(client_t *, char const *);
int use_thread(client_t *, char const *);
int use_channel(client_t *, char const *);

#endif // MY_SER //
