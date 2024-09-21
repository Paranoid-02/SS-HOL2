/*
============================================================================
Name - 32rem.c
Author - Akshay Sharma
Description - Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 2

sem_t *critical_section_sem;
sem_t *shared_memory_sem;
sem_t *resource_sem;

int shared_variable = 0;
int resources_available = NUM_RESOURCES;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // a. Protect critical section
    sem_wait(critical_section_sem);
    printf("Thread %d entered critical section\n", thread_id);
    sleep(1);
    printf("Thread %d exited critical section\n", thread_id);
    sem_post(critical_section_sem);

    // b. Protect shared memory from concurrent write access
    sem_wait(shared_memory_sem);
    shared_variable++;
    printf("Thread %d incremented shared variable to %d\n", thread_id, shared_variable);
    sem_post(shared_memory_sem);

    // c. Protect multiple pseudo resources using counting semaphore
    sem_wait(resource_sem);
    resources_available--;
    printf("Thread %d acquired a resource, %d resources left\n", thread_id, resources_available);
    sleep(2);
    resources_available++;
    printf("Thread %d released a resource, %d resources available\n", thread_id, resources_available);
    sem_post(resource_sem);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create named semaphores
    critical_section_sem = sem_open("/critical_section_sem", O_CREAT, 0644, 1);
    shared_memory_sem = sem_open("/shared_memory_sem", O_CREAT, 0644, 1);
    resource_sem = sem_open("/resource_sem", O_CREAT, 0644, NUM_RESOURCES);

    if (critical_section_sem == SEM_FAILED || shared_memory_sem == SEM_FAILED || resource_sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // d. Remove the created semaphores
    sem_close(critical_section_sem);
    sem_close(shared_memory_sem);
    sem_close(resource_sem);

    sem_unlink("/critical_section_sem");
    sem_unlink("/shared_memory_sem");
    sem_unlink("/resource_sem");

    printf("All semaphores have been removed\n");

    return 0;
}

/*
akshay~$cc 32rem.c 
akshay~$./a.out
Thread 0 entered critical section
Thread 0 exited critical section
Thread 0 incremented shared variable to 1
Thread 0 acquired a resource, 1 resources left
Thread 1 entered critical section
Thread 1 exited critical section
Thread 1 incremented shared variable to 2
Thread 2 entered critical section
Thread 1 acquired a resource, 0 resources left
Thread 0 released a resource, 1 resources available
Thread 2 exited critical section
Thread 2 incremented shared variable to 3
Thread 2 acquired a resource, 0 resources left
Thread 3 entered critical section
Thread 3 exited critical section
Thread 3 incremented shared variable to 4
Thread 4 entered critical section
Thread 1 released a resource, 1 resources available
Thread 3 acquired a resource, 0 resources left
Thread 4 exited critical section
Thread 4 incremented shared variable to 5
Thread 2 released a resource, 1 resources available
Thread 4 acquired a resource, 0 resources left
Thread 3 released a resource, 1 resources available
Thread 4 released a resource, 2 resources available
All semaphores have been removed
*/