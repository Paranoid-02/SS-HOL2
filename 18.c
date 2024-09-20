/*
============================================================================
Name : 18.c
Author : Akshay Sharma
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 17th Sept, 2024.
============================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

void execute_command(const char *command, int pipefd[]) {
    // Close the reading end of the pipe in the child
    close(pipefd[READ]);
    
    // Redirect stdout to the write end of the pipe
    if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    
    // Execute the command
    execl("/bin/sh", "sh", "-c", command, NULL);
    perror("execl");  // If execl returns, it's an error
    exit(EXIT_FAILURE);
}

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[256];
    int status;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {  // Child process
        execute_command("ls -l | grep ^d | wc -l", pipefd);
    } else {  // Parent process
        // Close the write end of the pipe in the parent
        close(pipefd[WRITE]);

        // Read from the pipe
        ssize_t count = read(pipefd[READ], buffer, sizeof(buffer) - 1);
        if (count > 0) {
            buffer[count] = '\0';
            printf("Number of directories: %s", buffer);
        } else {
            printf("No directories found or an error occurred.\n");
        }

        // Wait for the child to finish
        wait(&status);
    }

    return 0;
}

/*
akshay~$mkdir test
akshay~$./a.out   
Number of directories:        1
*/