/*
============================================================================
Name : 4.c
Author : Akshay Sharma
Description : Write a program to measure how much time is taken to execute 100 getppid () system call. Use time stamp counter.
Date: 16th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

// Function to read the TSC
unsigned long long int rdtsc() {
    unsigned long long int tm;
    __asm__ __volatile__ ("rdtsc" : "=A" (tm));
}

int main() {
    uint64_t start, end;
    int i;
    pid_t pid;

    // Warm up the CPU and cache
    for (i = 0; i < 1000; i++) {
        getppid();
    }

    // Start timing
    start = rdtsc();

    // Execute getppid() 100 times
    for (i = 0; i < 100; i++) {
        pid = getppid();
    }

    // End timing
    end = rdtsc();

    // Calculate cycles taken
    uint64_t cycles = end - start;

    printf("Time taken for 100 getppid() calls: %lu cycles\n", cycles);
    printf("Average time per getppid() call: %lu cycles\n", cycles / 100);

    return 0;
}