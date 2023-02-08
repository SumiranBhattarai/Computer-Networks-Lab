// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#define PORT 8001
#define MAXLINE 1024

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char result[30];
    struct sockaddr_in servaddr, cliaddr;
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
    // buffer[n] = '\0';

    printf("Client request: %s", buffer);
    // extract numbers from buffer

    int arr[n];
    int i, j, k = 0;
    int sum = 0;
    int count = 0;
    int temp = 0;

    for (i = 0; i < n; i++)
    {
        if (isdigit(buffer[i]))
        {
            temp = temp * 10 + (buffer[i] - '0');
        }
        else
        {
            arr[k++] = temp;
            sum += temp;
            temp = 0;
        }
    }
    arr[k++] = temp;
    sum += temp;

    printf("\nAverage is %f\n", (float)sum / k);

    sendto(sockfd, (const char *)result, strlen(result),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("\nResponse Sent\n");

    return 0;
}
