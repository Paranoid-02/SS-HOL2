/*
============================================================================
Name : 8c.c
Author : Akshay Sharma
Description : Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)
Date: 16th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigfpe_handler(int signum)
{
    printf("Caught SIGFPE (Floating-point Exception)\n");
    exit(1);
}

int main()
{
    signal(SIGFPE, sigfpe_handler);

    int a = 10, b = 0.0;
    int c = a / b;

    return 0;
}

/*

*/