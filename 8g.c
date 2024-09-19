/*
============================================================================
Name : 8g.c
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
    printf("Caught SIGPROF (Profiling Timer)\n");
}

int main() {
    signal(SIGPROF, handler);
    
    struct itimerval timer;
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_PROF, &timer, NULL);
    
    printf("Waiting for profiling timer...\n");
    while(1) {
        // Busy loop to consume CPU time
        for(int i = 0; i < 1000000; i++);
        
        // Sleep to simulate I/O or other non-CPU time
        usleep(10000);
    }
    
    return 0;
}

/*
akshay~$./a.out  
Waiting for profiling timer...
Caught SIGPROF (Profiling Timer)
*/