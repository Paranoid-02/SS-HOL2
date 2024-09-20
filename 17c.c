/*
============================================================================
Name : 17c.c
Author : Akshay Sharma
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date: 17th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork the first child process (ls -l)
    pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // Child process 1 (ls -l)
        
        // Close the read end of the pipe
        close(pipefd[PIPE_READ_END]);

        // Redirect stdout to the write end of the pipe
        if (dup2(pipefd[PIPE_WRITE_END], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        // Close the write end of the pipe
        close(pipefd[PIPE_WRITE_END]);

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    // Fork the second child process (wc)
    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // Child process 2 (wc)
        
        // Close the write end of the pipe
        close(pipefd[PIPE_WRITE_END]);

        // Redirect stdin to the read end of the pipe
        if (dup2(pipefd[PIPE_READ_END], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        // Close the read end of the pipe
        close(pipefd[PIPE_READ_END]);

        // Execute wc
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }

    // Parent process

    // Close both ends of the pipe
    close(pipefd[PIPE_READ_END]);
    close(pipefd[PIPE_WRITE_END]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}


/*
akshay~$./a.out
      34     299    1767
*/