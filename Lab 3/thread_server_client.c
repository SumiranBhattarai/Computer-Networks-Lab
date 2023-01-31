#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAX_CLIENTS 5
#define BUFFER_SIZE 100
void *handle_client(void *arg)
{
    int client_socket = *((int *)arg), i, sum = 0;
    int buffer[BUFFER_SIZE] = {0};
    int bytes_received;
    int n = recv(client_socket, &n, sizeof(n), 0);
    while (1)
    {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            break;
        }
    }
    for (int i = 1; i < n * sizeof(n); i++)
    {
        sum += buffer[i];
    }
    printf("\nSum is: %d\n", sum);
    close(client_socket);
    pthread_exit(NULL);
}
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_size;
    pthread_t client_thread;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = 6000;
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, MAX_CLIENTS);
    while (1)
    {
        client_address_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
        pthread_create(&client_thread, NULL, handle_client, &client_socket);
    }
    close(server_socket);
}