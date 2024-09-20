/*
============================================================================
Name : 26.c
Author : Akshay Sharma
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 18th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

#define MQ_NAME "/my_message_queue"
#define MQ_FLAGS O_CREAT | O_WRONLY

int main() {
    mqd_t mqd;
    struct mq_attr attr;
    char msg[] = "Hello, world!";

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;

    mqd = mq_open(MQ_NAME, MQ_FLAGS, 0666, &attr);
    if (mqd == -1) {
        perror("mq_open");
        exit(1);
    }

    if (mq_send(mqd, msg, sizeof(msg), 0) == -1) {
        perror("mq_send");
        exit(1);
    }

    printf("Message sent!\n");
    mq_close(mqd);
    return 0;
}   

/*
parallels@ubuntu-linux-22-04-02-desktop:~/Downloads$ ./a.out 
Message sent!
*/