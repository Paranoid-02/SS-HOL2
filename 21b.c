/*
============================================================================
Name : 21b.c
Author : Akshay Sharma
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME1 "myfifo1"
#define FIFO_NAME2 "myfifo2"

int main() {
  int fd1, fd2;
  char message[80];

  // Create FIFO pipes if they don't exist
  mkfifo(FIFO_NAME1, 0666);
  mkfifo(FIFO_NAME2, 0666);

  // Open FIFO pipes for reading and writing
  fd1 = open(FIFO_NAME1, O_RDONLY);
  fd2 = open(FIFO_NAME2, O_WRONLY);

  while (1) {
    // Receive message from FIFO1
    read(fd1, message, 80);
    printf("Received message: %s", message);

    printf("Enter message to send: ");
    fgets(message, 80, stdin);

    // Send message through FIFO2
    write(fd2, message, strlen(message) + 1);
  }

  close(fd1);
  close(fd2);
  return 0;
}

/*
akshay~$./fifo_receiver 
Received message: What up?
Enter message to send: Nothing Much, WBU?
Received message: Same here, all boring !
Enter message to send: yeaahhh
*/