/*
============================================================================
Name : 12.c
Author : Akshay Sharma
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 16th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        //Child Process
        printf("child process (PID: %d) is running \n",getpid());
        printf("parent process (PID: %d) will be terminated \n",getppid());

        sleep(1);

        if(kill(getppid(),SIGKILL) == 0){
            printf("SIGKILL sent to parent process. \n");
        }
        else{
            perror("Failed to send SIGKILL");
            exit(1);
        }
        
        sleep(1);

        if(getppid() == 1){
            printf("Child is now Orphan. \n");
        }

        sleep(30);
        printf("Child process (PID: %d) is exiting.\n", getpid());
    }else{
        printf("Parent process is running %d \n",getpid());
        sleep(60);
        printf("Parent process (PID: %d) is exiting.\n", getpid());
    }

    return 0;
}

/*
akshay~$./a.out
Parent process is running 19121
child process (PID: 19122) is running 
parent process (PID: 19121) will be terminated 
SIGKILL sent to parent process. 
zsh: killed     ./a.out
akshay~$Child is now Orphan. 
Child process (PID: 19122) is exiting.
*/