/*
============================================================================
Name : 10c.c
Author : Akshay Sharma
Description :Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 16th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler () {
    printf("SIGFPE handles \n");
    exit(1);
}
int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = 0;  
    sigemptyset(&sa.sa_mask);  

    if (sigaction(SIGFPE, &sa, NULL) == -1) 
        perror("sigaction error \n");

    int x = 5;
    int y =0;
    x = x/y;

    return 1;
}