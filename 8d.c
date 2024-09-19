/*
============================================================================
Name : 8d.c
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
#include <unistd.h>

void handler(int signum) {
    printf("Caught SIGALRM (Alarm)\n");
}

int main() {
    signal(SIGALRM, handler);
    
    alarm(5);  // Set alarm for 5 seconds
    
    printf("Waiting for alarm...\n");
    pause();  // Wait for a signal
    
    return 0;
}

/*
akshay~$./a.out
Waiting for alarm...
Caught SIGALRM (Alarm)
*/