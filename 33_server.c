/*
============================================================================
Name : 33.c
Author : Akshay Sharma
Description : Write a program to communicate between two machines using socket.
Date: 18 Aug 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 256

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
    char client_message[MAX_MESSAGE_LENGTH];
    char server_response[MAX_MESSAGE_LENGTH];

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 9002...\n");

    // Accept incoming connection
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
    if (client_socket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    while (1) {
        // Receive message from client
        int bytes_received = recv(client_socket, client_message, sizeof(client_message), 0);
        if (bytes_received <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        client_message[bytes_received] = '\0';
        printf("Received message from client: %s\n", client_message);

        if (strcmp(client_message, "quit") == 0) {
            printf("Client requested to quit.\n");
            break;
        }

        // Process the message (in this example, we'll just echo it back)
        snprintf(server_response, sizeof(server_response), "Server received: %s", client_message);

        // Send response back to client
        send(client_socket, server_response, strlen(server_response), 0);
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}