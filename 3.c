/*
============================================================================
Name : 3.c
Author : Akshay Sharma
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 16th Sept, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>

int main(){
    struct rlimit rl;
    // Get the current CPU time limit
    if (getrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("getrlimit");
        return 1;
    }

    printf("Current CPU time limit: soft = %ld, hard = %ld\n", 
           (long)rl.rlim_cur, (long)rl.rlim_max);
    
    // Set a new CPU time limit (e.g., 5 seconds)
    rl.rlim_cur = 5;
    rl.rlim_max = 5;
    
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("setrlimit");
        return 1;
    }
    
    printf("New CPU time limit set: soft = %ld, hard = %ld\n", 
           (long)rl.rlim_cur, (long)rl.rlim_max);
    
    // Verify the new limit
    if (getrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("getrlimit");
        return 1;
    }
    
    printf("Verified CPU time limit: soft = %ld, hard = %ld\n", 
           (long)rl.rlim_cur, (long)rl.rlim_max);
    
    // Simulate some CPU-intensive work
    printf("Starting CPU-intensive work...\n");
    for (long i = 0; i < 1000000000L; i++) {
        if (i % 100000000 == 0) {
            printf("Still working...\n");
        }
    }
    
    printf("Work completed without hitting the CPU time limit.\n");
    
    return 0;
}

/*
akshay~$cc 3.c
akshay~$./a.out
Current CPU time limit: soft = 9223372036854775807, hard = 9223372036854775807
New CPU time limit set: soft = 5, hard = 5
Verified CPU time limit: soft = 5, hard = 5
Starting CPU-intensive work...
Still working...
Still working...
Still working...
Still working...
Still working...
Still working...
Still working...
Still working...
Still working...
Still working...
Work completed without hitting the CPU time limit.
*/