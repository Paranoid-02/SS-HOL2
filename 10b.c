/*
============================================================================
Name : 10b.c
Author : Akshay Sharma
Description :Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
Date: 16th Sept, 2024.
============================================================================
*/

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void handler(int sig){
    write(STDOUT_FILENO,"\n Caught SIGINT! \n",19);
    exit(0);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = &handler;
    sigaction(SIGINT,&sa,NULL);

    while(1){
        sleep(1);
    }
}

/*
akshay~$./a.out
^CCaught SIGINT! 
*/

