/*
============================================================================
Name : 13a.c
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

void handler(int num){
    printf("Received signal %d (SIGSTOP) \n",num);
}

int main(){
    printf("Receiver process (PID: %d) is waiting for SIGSTOP...\n",getpid());

    if(signal(SIGSTOP,handler) == SIG_ERR){
        perror("Unable to catch SIGSTOP");
        printf("This is expected behavior as SIGSTOP cannot be caught.\n");
    }

    while(1){
        sleep(1);
    }

    return 0;
}

/*     
akshay~$./receiver          
Receiver process (PID: 23630) is waiting for SIGSTOP...
Unable to catch SIGSTOP: Invalid argument
This is expected behavior as SIGSTOP cannot be caught.
zsh: suspended (signal)  ./receiver
*/