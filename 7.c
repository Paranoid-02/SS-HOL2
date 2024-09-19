/*
============================================================================
Name : 7.c
Author : Akshay Sharma
Description : Write a simple program to print the created thread ids.
Date: 16th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void *alien_turn(void *arg) {
    printf("Current Thread ID: %lu \n",pthread_self());
    return NULL;
}
int main()
{
    pthread_t thread1, thread2, thread3;
    int p;
    p = pthread_create(&thread1, NULL, alien_turn, NULL);
    if(p!=0) perror("error");
    pthread_create(&thread2, NULL, alien_turn, NULL);
    if(p!=0) perror("error");
    pthread_create(&thread3, NULL, alien_turn, NULL);
    if(p!=0) perror("error");

    pthread_exit(NULL);
    // printf("Thread 1 ID: %lu\n", thread1);
    // printf("Thread 2 ID: %lu\n", thread2);
    // printf("Thread 3 ID: %lu\n", thread3);

    return 0;
}


/*
    printf("Thread 1 ID: %lu\n", thread1);
    printf("Thread 2 ID: %lu\n", thread2);
    printf("Thread 3 ID: %lu\n", thread3);
*/