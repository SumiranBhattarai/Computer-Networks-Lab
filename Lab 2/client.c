#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void main()
{
    struct sockaddr_in server, client;
    char str[30], res[40];
    int connected_socket;
    connected_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("Enter a string to check for palindrome: ");
    fgets(str, 30, stdin);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = htons(9000);
    printf("Connecting to server...\n");
    connect(connected_socket, &server, sizeof(server));
    printf("Connected\n");
    printf("Sending string to server...\n");
    send(connected_socket, &str, sizeof(str), 0);
    printf("waiting for response...\n");
    recv(connected_socket, &res, sizeof(res), 0);
    printf("Result: %s\n", res);
    printf("Closing connection...\n");
    close(connected_socket);
}