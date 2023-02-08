// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8000
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char result[30];
    struct sockaddr_in servaddr, cliaddr;
    int i;
    int j;
    int flag = 1;
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    int len, n;

    len = sizeof(cliaddr); // len is value/result

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);
    buffer[n] = '\0';

    for (i = 0; i < n / 2; i++)
    {
        if (buffer[i] != buffer[n - i - 1])
        {
            flag = 0;
            break;
        }
    }

    printf("Client request: %s", buffer);
    if (flag == 1)
    {
        printf("\nMessage is Palindrome");
        strcpy(result, "Palindrome");
    }
    else
    {
        printf("\nMessage is Not Palindrome");
        strcpy(result, "Not Palindrome");
    }
    sendto(sockfd, (const char *)result, strlen(result),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("\nResponse Sent\n");

    return 0;
}
