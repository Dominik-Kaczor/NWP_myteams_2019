/*
** EPITECH PROJECT, 2020
** constants
** File description:
** constants
*/

#ifndef MY_CST
#define MY_CST

static const size_t MAX_NAME_LENGTH = 32;
static const size_t MAX_DESCRIPTION_LENGTH = 255;
static const size_t MAX_BODY_LENGTH = 512;
static const int MAX_CLIENT_IN_SERVER = 50;
static const int EXIT_ERROR = 84;
static const char CRLF[] = "\r\n";
static const int BUF_SIZE = 1024;
static const char HELP_SERVER[] = "USAGE: ./myteams_server port\n\n\t \
portis the port number on which the server socket listens.\n";
static const char HELP_CLIENT[] = "USAGE: ./myteams_cli ip port\n\n\t\t \
ip\tis the server ip address on which the server socket listens\n\t\t \
port\tis the port number on which the server socket listens\n";
static const int INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;
static const int SELECT_ERROR = -1;
static const char BAD_ARGUMENTS[] = "Bad number of the arguments\n";
static const char PORT_INVALIDE[] = "Port is invalide\n\n";
static const char PORT_NOT_NUMBER[] = "The port is not number\n\n\n";
static const char BAD_SOCKET[] = "Socket failed";
static const char BAD_SETSOCKOPT[] = "Setsockopt failed";
static const char BAD_BIND[] = "Bind failed";
static const char BAD_LISTEN[] = "Listen failed";
static const char BAD_SELECT[] = "Select failed";
static const char BAD_HOSTINFO[] = "Hostinfo failed";
static const char BAD_CONNECT[] = "Connect failed";
static const char BAD_SEND[] = "Send failed";
static const char BAD_ACCEPT[] = "Accept failed";
static const char BAS_RECV[] = "Recv failed";

#endif // MY_CST //