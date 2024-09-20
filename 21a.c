/*
============================================================================
Name : 21a.c
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

  // Open FIFO pipes for writing and reading
  fd1 = open(FIFO_NAME1, O_WRONLY);
  fd2 = open(FIFO_NAME2, O_RDONLY);

  while (1) {
    printf("Enter message to send: ");
    fgets(message, 80, stdin);

    // Send message through FIFO1
    write(fd1, message, strlen(message) + 1);

    // Receive message from FIFO2
    read(fd2, message, 80);
    printf("Received message: %s", message);
  }

  close(fd1);
  close(fd2);
  return 0;
}

/*
akshay~$./fifo_sender            
Enter message to send: What up?
Received message: Nothing Much, WBU?
Enter message to send: Same here, all boring !
Received message: yeaahhh
Enter message to send: quit
*/