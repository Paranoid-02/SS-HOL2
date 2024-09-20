/*
============================================================================
Name : 20b.c
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

    printf("Receiver: Opening FIFO...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("Receiver: FIFO opened.\n");

    while (1) {
        // Read from the FIFO
        int bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            break;
        }

        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "quit") == 0) {
            break;
        }
    }

    close(fd);
    printf("Receiver: FIFO closed.\n");

    // Remove the FIFO
    unlink(FIFO_NAME);

    return 0;
}