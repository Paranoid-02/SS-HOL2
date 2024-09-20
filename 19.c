/*
============================================================================
Name : 19.c
Author : Akshay Sharma
Description : Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
Date: 17th Sept, 2024.
============================================================================
*/

//a-> mknod myfifo p
//b-> mkfifo myfifo
//c->strace mknod myfifo p or strace mkfifo myfifo

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    //d
    if (mknod("myfifo", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }
    printf("FIFO created successfully\n");

    //e
    if (mkfifo("myfifo", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO created successfully\n");
    return 0;
}

/*
akshay~$./a.out              
mknod: File exists
*/

/*
akshay~$time mknod myfifo p
mknod: myfifo: File exists
mknod myfifo p  0.00s user 0.00s system 60% cpu 0.006 total
akshay~$time mkfifo myfifo 
mkfifo: myfifo: File exists
mkfifo myfifo  0.00s user 0.00s system 49% cpu 0.005 total
*/