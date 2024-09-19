/*
============================================================================
Name : 11.c
Author : Akshay Sharma
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 16th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int num){
    write(STDOUT_FILENO,"I won't die ! \n",16);
}
int main(){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigaction(SIGINT,&sa,NULL);

    while(1){
        printf("Wasting your cycles xD %d\n",getpid());
        sleep(1);
    }
}

/*
Wasting your cycles xD 48028
Wasting your cycles xD 48028
^CI won't die ! 
Wasting your cycles xD 48028
Wasting your cycles xD 48028
^CI won't die ! 
Wasting your cycles xD 48028
Wasting your cycles xD 48028
*/