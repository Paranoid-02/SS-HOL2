/*
============================================================================
Name : 30.c
Author : Akshay Sharma
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date: 18th Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *data;
    
    // Generate a key for the shared memory
    if ((key = ftok(".", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // a. Attach to the shared memory and write some data
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    printf("Writing to shared memory...\n");
    strcpy(data, "Hello, Shared Memory!");
    printf("Data written: %s\n", data);

    // Detach from shared memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // b. Attach with O_RDONLY and try to overwrite
    data = shmat(shmid, (void *)0, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat (RDONLY)");
        exit(1);
    }

    printf("Attempting to overwrite in read-only mode...\n");
    if (strcpy(data, "Overwrite attempt") == NULL) {
        printf("Overwrite failed as expected in read-only mode.\n");
    } else {
        printf("Unexpected: Overwrite succeeded in read-only mode.\n");
    }

    printf("Current data in shared memory: %s\n", data);

    // c. Detach the shared memory
    if (shmdt(data) == -1) {
        perror("shmdt (RDONLY)");
        exit(1);
    }

    // d. Remove the shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory removed.\n");

    return 0;
}