#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 256

struct message 
{
    long mtype;
    char mtext[MAX_SIZE];
};

int main() 
{
    int msgid;
    key_t key;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok(".", 'x');

    // Create a message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) 
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Send a message to the message queue
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from the sender process!");
    if (msgsnd(msgid, &msg, sizeof(struct message) - sizeof(long), 0) == -1) 
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    // Receive a message from the message queue
    if (msgrcv(msgid, &msg, sizeof(struct message) - sizeof(long), 1, 0) == -1) 
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", msg.mtext);

    // Delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) 
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
