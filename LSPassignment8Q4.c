#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid2, pid3;

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
        sleep(2);
        printf("Process 2: Terminating\n");
        return 0;
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
            sleep(4);
            printf("Process 3: Terminating\n");
            return 0;
        }
    }

    // Wait for both child processes to terminate
    wait(NULL);
    wait(NULL);

    printf("Parent process: Terminating\n");
    return 0;
}


///
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 3
{
    pid_t pid2, pid3;
    int status;

    // Process 2
    pid2 = fork();

    if (pid2 == -1) 
    {
        perror("Failed to create Process 2");
        return 1;
    }

    if (pid2 == 0) 
    {
        // Child Process 2
        printf("Process 2: PID = %d\n", getpid());
        printf("Process 2: Parent PID = %d\n", getppid());

        execl("/bin/sleep", "sleep", "2", NULL);
        perror("Failed to execute sleep command");
        return 1;
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
            // Child Process 3
            printf("Process 3: PID = %d\n", getpid());
            printf("Process 3: Parent PID = %d\n", getppid());

            execl("/bin/sleep", "sleep", "4", NULL);
            perror("Failed to execute sleep command");
            return 1;
        }
    }

    // Parent process waits for both child processes to terminate
    waitpid(pid2, &status, 0);
    printf("Process 2 terminated\n");

    waitpid(pid3, &status, 0);
    printf("Process 3 terminated\n");

    printf("Parent process terminated\n");

    return 0;
}