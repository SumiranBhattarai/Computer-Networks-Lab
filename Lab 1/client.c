#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

void main()
{
    struct sockaddr_in server, client;
    int connected_socket;
    char str[30];
    printf("Enter a string: ");
    scanf("%s", str);
    connected_socket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = 6000;
    connect(connected_socket, &server, sizeof(server));
    send(connected_socket, &str, sizeof(str), 0);
    close(connected_socket);
}