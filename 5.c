/*
============================================================================
Name : 5.c
Author : Akshay Sharma
Description : Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory.
Date: 16th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    long val;
    val = sysconf(_SC_ARG_MAX);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("maximum length of the arguments to the exec family of functions : %ld", val);
    printf("\n");
    val = sysconf(_SC_CHILD_MAX);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("maximum number of simultaneous process per user id : %ld", val);
    printf("\n");
    val = sysconf(_SC_ARG_MAX);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("number of clock ticks (jiffy) per second : %ld", val);
    printf("\n");
    val = sysconf(_SC_OPEN_MAX);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("maximum number of open files : %ld", val);
    printf("\n");
    val = sysconf(_SC_PAGESIZE);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("size of a page : %ld", val);
    printf("\n");
    val = sysconf(_SC_PHYS_PAGES);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("total number of pages in the physical memory : %ld", val);
    printf("\n");
    val = sysconf(_SC_AVPHYS_PAGES);
    if (val == -1)
    {
        perror("error");
        return 1;
    }
    printf("number of currently available pages in the physical memory. : %ld", val);
}

/*
parallels@ubuntu-linux-22-04-02-desktop:~/Downloads/HOL@$ ./a.out
maximum length of the arguments to the exec family of functions : 2097152
maximum number of simultaneous process per user id : 7281
number of clock ticks (jiffy) per second : 2097152
maximum number of open files : 1024
size of a page : 4096
total number of pages in the physical memory : 503629
number of currently available pages in the physical memory. : 61186
*/