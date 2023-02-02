#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>

#define DATA_BUFFER 5000
#define MAX_CONNECTIONS 100

fd_set read_fd_set;

struct sockaddr_in new_addr;
int server_fd, new_fd;
socklen_t addrlen;
char buf[DATA_BUFFER];

pid_t childpid;

int create_tcp_server_socket()
{
    struct sockaddr_in saddr;
    int fd, ret_val;
    int opt = 1;

    /* Step1: create a TCP socket */
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1)
    {
        fprintf(stderr, "socket failed [%s]\n", strerror(errno));
        return -1;
    }
    printf("Created a socket with fd: %d\n", fd);

    // reuse open port
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    /* Initialize the socket address structure */
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(7000);
    saddr.sin_addr.s_addr = INADDR_ANY;

    /* Step2: bind the socket to port 7000 on the local host */
    ret_val = bind(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
    if (ret_val != 0)
    {
        fprintf(stderr, "bind failed [%s]\n", strerror(errno));
        close(fd);
        return -1;
    }

    /* Step3: listen for incoming connections */
    ret_val = listen(fd, 100);
    if (ret_val != 0)
    {
        fprintf(stderr, "listen failed [%s]\n", strerror(errno));
        close(fd);
        return -1;
    }
    return fd;
}

void read_write()
{
    int i, ret_val, flag = 0, num;
    FD_ZERO(&read_fd_set);

    while (1)
    {
        FD_SET(server_fd, &read_fd_set); // start reading for in-coming

        printf("\nUsing select() to listen for incoming events\n");
        ret_val = select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL);

        printf("Select returned with %d\n", ret_val);

        if (FD_ISSET(server_fd, &read_fd_set))
        {

            printf("Returned fd is %d (server's fd)\n", server_fd);
            new_fd = accept(server_fd, (struct sockaddr *)&new_addr, &addrlen);

            printf("Accepted a new connection with fd: %d\n", new_fd);

            if ((childpid = fork()) == 0)
            {
                printf("\n Child process id : %d", getpid());
                close(server_fd);

                bzero(&buf, sizeof(buf));
                if (read(new_fd, buf, sizeof(buf)) <= 0)
                    perror("rec");
                printf("\n Message from client : %s", buf);
                num = atoi(buf);
                printf("\nThe given number is");
                if (num % 2 == 0)
                {
                    printf(": Even\n");
                    strcpy(buf, "Even");
                }
                else
                {
                    printf(": Odd\n");
                    strcpy(buf, "Odd");
                }
                write(new_fd, buf, sizeof(buf));

                close(new_fd);
                exit(0);
            };             // end of if child process
            close(new_fd); // close by parent
        }                  // end of FD_ISSET
    }                      // end of while
} // end of read

int main()
{
    int i;

    /* Get the socket server fd */
    server_fd = create_tcp_server_socket();
    if (server_fd == -1)
    {
        fprintf(stderr, "Failed to create a server\n");
        return -1;
    }

    read_write();
    return 0;
}
