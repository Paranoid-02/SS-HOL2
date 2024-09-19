/*
============================================================================
Name : 6.c
Author : Akshay Sharma
Description : Write a simple program to create three threads.
Date: 16th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *my_turn(void *arg) {
    int i;

    for (i = 0; i < 5; i++) {
        printf("My Turn \n");
        sleep(1);
    }

    return NULL;
}
void *your_turn(void *arg) {
    int i;

    for (i = 0; i < 8; i++) {
        printf("Your Turn \n");
        sleep(1);
    }

    return NULL;
}
void *alien_turn(void *arg) {
    int i;

    for (i = 0; i < 3; i++) {
        printf("Alien's Turn \n");
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;
    int p;
    p = pthread_create(&thread1, NULL, my_turn, NULL);
    if(p!=0) perror("error");
    pthread_create(&thread2, NULL, your_turn, NULL);
    if(p!=0) perror("error");
    pthread_create(&thread3, NULL, alien_turn, NULL);
    if(p!=0) perror("error");

    // pthread_exit(NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("All threads have finished.\n");

    return 0;
}

/*
akshay~$./a.out
My Turn 
Your Turn 
Alien's Turn 
My Turn 
Alien's Turn 
Your Turn 
Alien's Turn 
My Turn 
Your Turn 
My Turn 
Your Turn 
Your Turn 
My Turn 
Your Turn 
Your Turn 
Your Turn 
All threads have finished.
*/