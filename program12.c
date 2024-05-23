#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_sock;
    struct sockaddr_in server_addr;
    int buffer[2], result;
    ssize_t sent_bytes, recv_bytes;

    // Create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        perror("[-]Socket error");
        exit(EXIT_FAILURE);
    }
    printf("[+]Client socket created.\n");

    // Configure settings
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7799);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("[-]Connect error");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+]Connected to server.\n");

    // Send data
    buffer[0] = 10; // a
    buffer[1] = 20; // b
    sent_bytes = send(client_sock, buffer, sizeof(buffer), 0);
    if (sent_bytes < 0)
    {
        perror("[-]Send error");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+]Data sent.\n");

    // Receive result
    recv_bytes = recv(client_sock, &result, sizeof(result), 0);
    if (recv_bytes < 0)
    {
        perror("[-]Receive error");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    else if (recv_bytes == 0)
    {
        printf("[-]Server closed the connection unexpectedly.\n");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    printf("[+]Result received: %d\n", result);

    // Close the socket
    close(client_sock);
    printf("[+]Connection closed.\n");

    return 0;
}
