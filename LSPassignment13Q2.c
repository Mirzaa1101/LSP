#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal_number) 
{
    if (signal_number == SIGUSR1) 
    {
        printf("Received SIGUSR1 signal from the parent process\n");
    }
}

int main() 
{
    pid_t pid;
    
    // Create the child process
    pid = fork();
    
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        // Child process
        signal(SIGUSR1, signal_handler);
        
        while (1) 
        {
            // Child process loop
        }
        
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        sleep(1);  // Wait for child process to initialize signal handler
        
        printf("Sending SIGUSR1 signal to the child process\n");
        kill(pid, SIGUSR1);
        
        exit(EXIT_SUCCESS);
    }
}