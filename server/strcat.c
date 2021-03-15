/*
** EPITECH PROJECT, 2020
** strcat
** File description:
** strcat
*/

#include "server.h"

char *my_strcat(char *one, char const *two)
{
    char *final = malloc(sizeof(char) * (strlen(one) + strlen(two) + 1));
    int i = 0;
    int k = 0;

    for (; one[i]; i++)
    	final[i] = one[i];
    while (two[k]) {
        final[i] = two[k];
        i++;
        k++;
    }
    final[i] = '\0';
    return (final);
}

void message_file(client_t *clients, int sender, const char **array)
{
    FILE *fp;
    char buff[20];
    memset(buff, 0, 20);
    time_t timestamp = time(NULL);
    struct tm *ptime = localtime(&timestamp);
    struct stat info;

    stat("./server/send.c", &info);
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", ptime);
    fp = fopen ("./.data_base/.messages/.msg.txt", "a");
    fprintf(fp, "%s|%s|%s|%s\n", clients[sender].id, array[1], array[2], buff);
    fclose(fp);
    server_event_private_message_sended(clients[sender].id, array[1],
        array[2]);
}

char **tab_infos(char *infos, char delim)
{
    char **res = malloc(sizeof(char *) * (get_char(infos, delim) + 2));
    char *delim_s = malloc(sizeof(char) * 2);
    char *p = NULL;
    int i = 0;

    delim_s[0] = delim;
    delim_s[1] = '\0';
    p = strtok(infos, delim_s);
    while (p != NULL) {
        res[i++] = strdup(p);
        p = strtok(NULL, delim_s);
    }
    res[i] = NULL;
    return res;
}