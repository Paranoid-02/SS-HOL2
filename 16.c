/*
============================================================================
Name : 16.c
Author : Akshay Sharma
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
date: 17th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>

int main(){
    int p1[2];//C->P
    int p2[2];//P->C
    if(pipe(p1) == -1){
        return 1;
    }
    if(pipe(p2) == -1){
        return 1;
    }
    int pid = fork();
    if(pid == -1) {return 2;}
    else if(pid == 0){
        //Child Process
        close(p1[0]);
        close(p2[1]);
        int x;
        if(read(p2[0],&x,sizeof(x)) == -1){return 3;}
        printf("Child->received %d\n",x);
        x *= 4;
        if(write(p1[1],&x,sizeof(x)) == -1){return 4;}
        printf("Child->wrote %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }else{
        close(p1[1]);
        close(p2[0]);
        //Parent Process
        srand(time(NULL));
        int y = rand() % 10;
        if(write(p2[1],&y,sizeof(y)) == -1){return 5;}
        printf("Parent->Wrote %d\n",y);
        if(read(p1[0],&y,sizeof(y)) == -1){return 6;}
        printf("Result is %d\n",y);
        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}

/*
akshay~$./a.out
Parent->Wrote 9
Child->received 9
Child->wrote 36
Result is 36
*/