/*
** EPITECH PROJECT, 2020
** read
** File description:
** read
*/

#include "server.h"

int read_client(int sock, char *buffer)
{
    int n = 0;

    if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0) {
        perror("recv()");
        n = 0;
    }
    buffer[n] = 0;
    return n;
}