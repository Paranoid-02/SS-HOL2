/*
============================================================================
Name : 1a.c
Author : Akshay Sharma
Description : ITIMER_REAL
Date: 13th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

void timer_handler(int signum){
    printf("ITIMER_REAL timer expired\n");
}

int main(){
    struct itimerval timer;
    //signal handler
    signal(SIGALRM,timer_handler);
    //timer
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    //expiration
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if(setitimer(ITIMER_REAL,&timer,NULL)==-1){
        perror("Error setting timer");
        exit(EXIT_FAILURE);
    }

    while(1){
        pause();
    }
    
    return 0;
}

/*output
ITIMER_REAL timer expired
ITIMER_REAL timer expired
^C
*/