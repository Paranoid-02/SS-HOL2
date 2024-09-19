/*
============================================================================
Name : 8a.c
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

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void handler(int num){
    printf("Caught SIGSEGV signal!\n");
    exit(0);
}
int main(){
    int *p = NULL;
    signal(SIGSEGV,handler);
    *p = 45;
}

/*
akshay~$./a.out
Caught SIGSEGV signal!
akshay~$
*/