/*
============================================================================
Name : 13b.c
Author : Akshay Sharma
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 17th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr,"Usage: %s <PID> \n",argv[0]);
        exit(1);
    }

    pid_t pid = atoi(argv[1]);

    printf("Sending SIGSTOP to process %d\n",pid);
    if(kill(pid,SIGSTOP) == -1){
        perror("Failed to send SIGSTOP");
        exit(1);
    }

    printf("SIGSTOP SENT SUCCESSFULLY\n");
    return 0;
}

/*
akshay~$./sender 23630
Sending SIGSTOP to process 23630
SIGSTOP SENT SUCCESSFULLY
*/