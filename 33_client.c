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
#include <arpa/inet.h>

#define MAX_MESSAGE_LENGTH 256

int main() {
    int network_socket;
    struct sockaddr_in server_address;
    char message[MAX_MESSAGE_LENGTH];
    char server_response[MAX_MESSAGE_LENGTH];

    // Create socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Specify an address for socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Use localhost

    // Connect to the server
    if (connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    while (1) {
        // Get user input
        printf("Enter message (or 'quit' to exit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;  // Remove newline

        // Send message to server
        send(network_socket, message, strlen(message), 0);

        if (strcmp(message, "quit") == 0) {
            printf("Disconnecting from server.\n");
            break;
        }

        // Receive response from server
        int bytes_received = recv(network_socket, server_response, sizeof(server_response), 0);
        if (bytes_received > 0) {
            server_response[bytes_received] = '\0';
            printf("Server response: %s\n", server_response);
        }
    }

    // Close socket
    close(network_socket);

    return 0;
}