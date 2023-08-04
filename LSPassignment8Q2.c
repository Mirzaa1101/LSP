#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid1, pid2, pid3;

    // Process 1 creates Process 2
    pid1 = fork();

    if (pid1 == -1) 
    {
        perror("Failed to create Process 2");
        return 1;
    }

    if (pid1 == 0) 
    {
        // Process 2 creates Process 3
        pid2 = fork();

        if (pid2 == -1) 
        {
            perror("Failed to create Process 3");
            return 1;
        }

        if (pid2 == 0)
        {
            // Process 3
            printf("Process 3: PID = %d\n", getpid());
            printf("Process 3: Parent PID = %d\n", getppid());
        } 
        else 
        {
            // Process 2
            printf("Process 2: PID = %d\n", getpid());
            printf("Process 2: Parent PID = %d\n", getppid());

            // Wait for Process 3 to terminate
            wait(NULL);
        }
    } 
    else 
    {
        // Process 1
        printf("Process 1: PID = %d\n", getpid());

        // Wait for Process 2 to terminate
        wait(NULL);
    }

    return 0;
}