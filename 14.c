/*
============================================================================
Name : 14.c
Author : Akshay Sharma
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 17th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main(){
    int fd[2];
    //fd[0] - read
    //fd[1] - write
    char buffer[100];
    char* message = "Hello pipe!";

    if(pipe(fd) == -1){
        perror("error");
        exit(1);
    }

    printf("Pipe created succesfully\n");
    //Write to the pipe
    ssize_t byteswritten = write(fd[1], message, strlen(message));
    if(byteswritten == -1){
        perror("write");
        exit(1);
    }
        printf("Wrote %ld bytes to the pipe: %s\n", byteswritten, message);

    // Read from the pipe
    ssize_t bytes_read = read(fd[0], buffer, 100);
    if (bytes_read == -1) {
        perror("read");
        exit(1);
    }

    buffer[bytes_read] = '\0';

    // Display the read content
    printf("Read %ld bytes from the pipe: %s\n", bytes_read, buffer);

    // Close the pipe
    close(fd[0]);
    close(fd[1]);

    return 0;

}

/*
akshay~$./a.out
Pipe created succesfully
Wrote 11 bytes to the pipe: Hello pipe!
Read 11 bytes from the pipe: Hello pipe!
*/