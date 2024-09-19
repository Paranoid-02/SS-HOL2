/*
============================================================================
Name : 10a.c
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
    write(STDOUT_FILENO,"\n Caught SIGSEGV! \n",20);
    exit(0);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = &handler;
    sigaction(SIGSEGV,&sa,NULL);

    float x = 10;
    int *p = NULL;
    *p = 32;
    return 0;
}

/*
akshay~$./a.out 
 Caught SIGSEGV! 
 */