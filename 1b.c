/*
====================
Name : 1b.c
Author : Akshay Sharma
Description : ITIMER_VIRTUAL
Date: 13th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum)
{
    printf("ITIMER_VIRTUAL timer expired\n");
}

int main()
{
    struct itimerval timer;

    // signal handler
    signal(SIGVTALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    // Start the timer
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
    {
        perror("Error setting timer");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running
    while (1)
    {
        for (volatile int i = 0; i < 100000000; i++);
        pause(); // Wait for signal
    }

    return 0;
}