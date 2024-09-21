/*
============================================================================
Name : 34b.c
Author : Akshay Sharma
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date: 18 Aug 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    char buffer[1024];
    int bytes_read;

    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received message: %s\n", buffer);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Create thread to handle client
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

/*
server->
parallels@ubuntu-linux-22-04-02-desktop:~/Downloads$ ./a.out
Server listening on port 8080...
Received message: hello

Received message: this is client

client->
parallels@ubuntu-linux-22-04-02-desktop:~/Downloads$ telnet localhost 8080
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
hello
hello
this is client  
this is client
nice
nice
Connection closed by foreign host.
*/