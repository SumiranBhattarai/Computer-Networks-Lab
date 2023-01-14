#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
void main()
{
    struct sockaddr_in server, client;
    int listening_socket, connected_socket, server_len, i, j, k, l;
    char str[30];
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = 6000;
    bind(listening_socket, &server, sizeof(server));
    listen(listening_socket, 5);
    server_len = sizeof(client);
    connected_socket = accept(listening_socket, &client, &server_len);
    recv(connected_socket, &str, sizeof(str), 0);
    printf("Received string is: %s", str);
    close(connected_socket);
    close(listening_socket);
}