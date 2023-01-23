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
    if (connected_socket == -1)
    {
        printf("Could not create socket");
    }
    printf("Enter a string to check for palindrome: ");
    scanf("%s", str);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(9000);

    if (connect(connected_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    printf("Sending string to server...\n");
    if (send(connected_socket, str, strlen(str), 0) < 0)
    {
        printf("Send failed");
        return 1;
    }
    printf("waiting for response...\n");
    if (recv(connected_socket, &res, sizeof(res), 0) < 0)
    {
        printf("recv failed");
    }
    printf("Result: %s\n", res);
    printf("Closing connection...\n");
    close(connected_socket);
}