/*
============================================================================
Name : 17b.c
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
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {  // Child process (ls -l)
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    } else {  // Parent process (wc)
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp wc");
        exit(1);
    }

    return 0;
}

/*
akshay~$./a.out 
total 440
-rw-r--r--  1 akshay  staff    726 Sep 18 19:31 10a.c
-rw-r--r--  1 akshay  staff    698 Sep 18 19:35 10b.c
-rw-r--r--  1 akshay  staff    741 Sep 18 19:34 10c.c
-rw-r--r--  1 akshay  staff    913 Sep 18 19:39 11.c
-rw-r--r--  1 akshay  staff   1631 Sep 19 09:24 12.c
-rw-r--r--  1 akshay  staff   1162 Sep 19 10:51 13a.c
.
.
.
.
*/