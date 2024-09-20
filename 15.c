/*
============================================================================
Name : 15.c
Author : Akshay Sharma
Description : Write a simple program to send some data from parent to the child process.
Date: 17th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main(){
    int fd[2];
    if(pipe(fd) == -1){
        perror("error");
        exit(1);
    }

    int id = fork();
    if(id == -1){
        perror("fork failed");
    }
    else if(id == 0){
        //child process
        close(fd[0]);
        int x;
        printf("Child here , Enter an interger\n");
        scanf("%d",&x);
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
    }else{
        //parent process
        close(fd[1]);
        int y;
        read(fd[0],&y,sizeof(int));
        close(fd[0]);
        printf("Parent here, Got from child process %d\n",y);
    }
    return 0;
}

/*
akshay~$./a.out
Child here , Enter an interger
5
Parent here, Got from child process 5
*/
