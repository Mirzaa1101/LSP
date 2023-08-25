#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void receiver_handler(int signal) 
{
    printf("Signal received from sender\n");
}

int main() 
{
    pid_t pid;

    // Fork the process
    pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) 
    {
        // Parent process (sender)
        printf("Sender process sending signal to receiver process\n");

        // Sleep for 1 second to allow the receiver process to set up the signal handler
        sleep(1);

        // Send a signal to the receiver process
        kill(pid, SIGUSR1);
    } 
    else 
    {
        // Child process (receiver)
        // Set up the signal handler
        signal(SIGUSR1, receiver_handler);

        printf("Receiver process waiting for signal\n");

        // Sleep indefinitely to keep the receiver process alive
        while (1) 
        {
            sleep(1);
        }
    }

    return 0;
}