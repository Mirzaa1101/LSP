#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid2, pid3, pid4;

    // Process 2
    pid2 = fork();

    if (pid2 == -1) 
    {
        perror("Failed to create Process 2");
        return 1;
    }

    if (pid2 == 0) 
    {
        printf("Process 2: PID = %d\n", getpid());
        printf("Process 2: Parent PID = %d\n", getppid());
    } 
    else 
    {
        // Process 3
        pid3 = fork();

        if (pid3 == -1) 
        {
            perror("Failed to create Process 3");
            return 1;
        }

        if (pid3 == 0) 
        {
            printf("Process 3: PID = %d\n", getpid());
            printf("Process 3: Parent PID = %d\n", getppid());
        } 
        else 
        {
            // Process 4
            pid4 = fork();

            if (pid4 == -1) 
            {
                perror("Failed to create Process 4");
                return 1;
            }

            if (pid4 == 0)
            {
                printf("Process 4: PID = %d\n", getpid());
                printf("Process 4: Parent PID = %d\n", getppid());
            }
        }
    }

    // Wait for all child processes to terminate
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}