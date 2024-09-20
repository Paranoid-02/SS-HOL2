/*
============================================================================
Name : 31.c
Author : Akshay Sharma
Description : Write a program to create a semaphore and initialize value to the semaphore.
Date: 18 Aug 2024
============================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define THREAD_NUM 4
#define INITIAL_VAL 2 // 1 for binary semaphore, more than 1 for counting semaphore
#define SEM_NAME "/semubhai"

sem_t *semaphore;

void* routine(void* args) {
    sem_wait(semaphore);
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    sem_post(semaphore);
    free(args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    
    // Create a semaphore
    semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, INITIAL_VAL);
    if (semaphore == SEM_FAILED) {
        perror("Failed to create semaphore");
        return 1;
    }
    
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread");
            free(a);
            sem_close(semaphore);
            sem_unlink(SEM_NAME);
            return 1;
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
            sem_close(semaphore);
            sem_unlink(SEM_NAME);
            return 1;
        }
    }
    
    // Close and unlink the semaphore
    if (sem_close(semaphore) != 0) {
        perror("Failed to close semaphore");
        sem_unlink(SEM_NAME);
        return 1;
    }
    
    if (sem_unlink(SEM_NAME) != 0) {
        perror("Failed to unlink semaphore");
        return 1;
    }
    
    return 0;
}


/*
akshay~$./a.out            
Hello from thread 0
Hello from thread 1
Hello from thread 2
Hello from thread 3
*/