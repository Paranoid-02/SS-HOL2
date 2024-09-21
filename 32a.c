/*
============================================================================
Name - 32a.c
Author - Akshay Sharma
Description - Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

struct {
    int train_num;
    int train_count;
} db;

int main() {
    int fd, input;
    fd = open("record.txt", O_RDWR);

    printf("Enter the train number 1, 2, or 3: ");
    scanf("%d", &input);

    char sem_name[20];
    sprintf(sem_name, "/train_%d_semaphore", input);
    sem_t *trainSemaphore = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR, 1);

    sem_wait(trainSemaphore); 

    lseek(fd, (input - 1) * sizeof(db), SEEK_SET);
    read(fd, &db, sizeof(db));
    printf("Before entering the critical section\n");

    printf("Ticket number is %d\n", db.train_count);
    db.train_count++;
    lseek(fd, -sizeof(db), SEEK_CUR);
    write(fd, &db, sizeof(db));
    printf("Confirm your ticket by pressing enter\n");
    getchar();
    getchar();

    sem_post(trainSemaphore); 

    close(fd);
    sem_close(trainSemaphore);

    printf("Booked\n");

    return 0;
}

/*
akshay~$./a.out 
Enter the train number 1, 2, or 3: 2
Before entering the critical section
Ticket number is 0
Confirm your ticket by pressing enter

Booked
akshay~$./a.out
Enter the train number 1, 2, or 3: 1
Before entering the critical section
Ticket number is 0
Confirm your ticket by pressing enter

Booked
*/