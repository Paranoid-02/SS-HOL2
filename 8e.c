/*
============================================================================
Name : 8e.c
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
#include <sys/time.h>
#include <unistd.h>

void handler(int signum) {
    printf("Caught SIGALRM (Alarm)\n");
}

int main() {
    signal(SIGALRM, handler);
    
    struct itimerval timer;
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("Waiting for alarm...\n");
    pause();  // Wait for a signal
    
    return 0;
}

/*
akshay~$./a.out
Waiting for alarm...
Caught SIGALRM (Alarm)
*/