/*
============================================================================
Name : 20a.c
Author : Akshay Sharma
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 17th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Create the FIFO if it doesn't exist
    mkfifo(FIFO_NAME, 0666);

    printf("Sender: Opening FIFO...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("Sender: FIFO opened.\n");

    while (1) {
        printf("Enter message (or 'quit' to exit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Write the message to the FIFO
        write(fd, buffer, strlen(buffer) + 1);

        if (strcmp(buffer, "quit") == 0) {
            break;
        }
    }

    close(fd);
    printf("Sender: FIFO closed.\n");

    return 0;
}