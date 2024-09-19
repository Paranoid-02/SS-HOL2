/*
============================================================================
Name : 9.c
Author : Akshay Sharma
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 16th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void handler(int num){
    write(STDOUT_FILENO,"I won't die ! \n",13);
}
int main(){
    signal(SIGINT,handler);
    // signal(SIGTERM,handler);
    while(1){
        printf("Wasting your cycles xD %d\n",getpid());
        sleep(1);
    }
}

/*
akshay~$cc 9.c 
akshay~$./a.out
Wasting your cycles xD 32262
Wasting your cycles xD 32262
Wasting your cycles xD 32262
Wasting your cycles xD 32262
Wasting your cycles xD 32262
^CI won't die !Wasting your cycles xD 32262
Wasting your cycles xD 32262
Wasting your cycles xD 32262
^CI won't die !Wasting your cycles xD 32262
zsh: terminated  ./a.out
*/