#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void main()
{
    struct sockaddr_in server, client;
    int listening_socket, connected_socket, i, server_len, j, flag = 0;
    char str[30], rev[30], res[40];
    listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(INADDR_ANY);
    server.sin_port = htons(9000);
    bind(listening_socket, &server, sizeof(server));
    listen(listening_socket, 5);
    server_len = sizeof(client);
    connected_socket = accept(listening_socket, &client, &server_len);
    printf("Client connected\n");
    printf("\nReceiving string from client...\n");
    recv(connected_socket, str, sizeof(str), 0);
    printf("\nReceived string: %s\n", str);
    j = strlen(str);
    for (i = 0; i < j; i++)
    {
        if (str[i] != str[j - i - 1])
        {
            flag = 1;
            break;
        }
    }
    if (flag != 0)
    {
        strcpy(res, "The string is a palindrome");
    }
    else
    {
        strcpy(res, "The string is not palindrome");
    }
    printf("%s\n", res);
    printf("Sending response to client...\n");
    send(connected_socket, res, strlen(res), 0);
    printf("closing connection...\n");
    close(connected_socket);
    close(listening_socket);
}