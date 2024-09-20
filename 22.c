/*
============================================================================
Name : 22.c
Author : Akshay Sharma
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>

#define FIFO_NAME "myfifo"

int main() {
  int fd;
  char buffer[80];
  fd_set readfds;
  struct timeval timeout;

  mkfifo(FIFO_NAME, 0666);

  // Open FIFO for reading
  fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK); 
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  printf("Waiting for data on FIFO...\n");

  while (1) {
    // Initialize the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Use select to wait for data or timeout
    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
      perror("select");
      exit(1);
    } else if (ret == 0) {
      printf("Timeout: No data received within 10 seconds.\n");
      break;
    } else {
      // Data is available on the FIFO
      int bytes_read = read(fd, buffer, sizeof(buffer));
      if (bytes_read > 0) {
        printf("Data received: %s\n", buffer);
      }
    }
  }

  close(fd);
  return 0;
}

/*
akshay~$./a.out
Waiting for data on FIFO...
Data received: Hello from FIFO again
*/