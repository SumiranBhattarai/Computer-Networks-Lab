#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define DATA_BUFFER "Mona Lisa was painted by Leonardo da Vinci"

int main()
{
    struct sockaddr_in saddr;
    int fd, ret_val;
    struct hostent *local_host; /* need netdb.h for this */
    char c[1024];

    /* Step1: create a TCP socket */
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1)
    {
        fprintf(stderr, "socket failed [%s]\n", strerror(errno));
        return -1;
    }
    printf("Created a socket with fd: %d\n", fd);

    /* Let us initialize the server address structure */
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(7000);
    local_host = gethostbyname("127.0.0.1");
    saddr.sin_addr = *((struct in_addr *)local_host->h_addr);

    /* Step2: connect to the TCP server socket */
    ret_val = connect(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
    if (ret_val == -1)
    {
        fprintf(stderr, "connect failed [%s]\n", strerror(errno));
        close(fd);
        return -1;
    }
    printf("The Socket is now connected\n");

    // printf("Let us sleep before we start sending data\n");
    //  sleep(5);
    printf("\n Enter the number : ");
    fgets(c, 1024, stdin);
    /* Next step: send some data */
    ret_val = send(fd, c, sizeof(c), 0);
    // ret_val = send(fd,DATA_BUFFER, sizeof(DATA_BUFFER), 0);
    printf("Successfully sent data (len %d bytes): %s\n", ret_val, c);
    bzero(&c, 0);
    recv(fd, c, sizeof(c), 0);
    printf("\n Message received : %s", c);
    /* Last step: close the socket */
    close(fd);
    return 0;
}
