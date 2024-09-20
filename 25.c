/*
============================================================================
Name : 25.c
Author : Akshay Sharma
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 18th Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    key_t messageQueueKey;
    int messageQueueId;
    struct msqid_ds messageQueueInfo;
    int msgctlResult;

    messageQueueKey = ftok(".", 1);
    if (messageQueueKey == -1) {
        perror("Error while computing key!");
        _exit(1);
    }

    messageQueueId = msgget(messageQueueKey, IPC_CREAT | 0700);
    if (messageQueueId == -1) {
        perror("Error while creating Message Queue!");
        _exit(1);
    }

    msgctlResult = msgctl(messageQueueId, IPC_STAT, &messageQueueInfo);
    if (msgctlResult == -1) {
        perror("Error while getting Message Queue info!");
        _exit(1);
    }

    printf("Message Queue Information:\n");
    printf("a. Access Permission: %o\n", messageQueueInfo.msg_perm.mode);
    printf("b. UID: %d, GID: %d\n", messageQueueInfo.msg_perm.uid, messageQueueInfo.msg_perm.gid);
    printf("c. Time of last message sent: %ld, Time of last message received: %ld\n", messageQueueInfo.msg_stime, messageQueueInfo.msg_rtime);
    printf("d. Time of last change in the message queue: %ld\n", messageQueueInfo.msg_ctime);
    printf("e. Size of the queue: %ld\n", messageQueueInfo.__msg_cbytes);
    printf("f. Number of messages in the queue: %ld\n", messageQueueInfo.msg_qnum);
    printf("g. Maximum number of bytes allowed: %ld\n", messageQueueInfo.msg_qbytes);
    printf("h. PID of the last sent message: %d, PID of the last received message: %d\n", messageQueueInfo.msg_lspid, messageQueueInfo.msg_lrpid);

    return 0;
}

/*
parallels@ubuntu-linux-22-04-02-desktop:~/Downloads$ ./a.out 
Message Queue Information:
a. Access Permission: 700
b. UID: 1000, GID: 1000
c. Time of last message sent: 0, Time of last message received: 0
d. Time of last change in the message queue: 1726858238
e. Size of the queue: 0
f. Number of messages in the queue: 0
g. Maximum number of bytes allowed: 16384
h. PID of the last sent message: 0, PID of the last received message: 0
*/