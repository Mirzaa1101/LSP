
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
    pid_t pid = fork();

    if (pid == -1) 
    {
        perror("Failed to fork");
        return 1;
    }

    if (pid == 0) 
    {
        // Child process
        printf("Child process\n");
        sleep(5);
        printf("Child process finished\n");
        return 0;
    } 
    else 
    {
        // Parent process
        printf("Parent process\n");

        int status;
        pid_t terminated_pid = wait(&status);

        if (terminated_pid == -1) 
        {
            perror("Failed to wait");
            return 1;
        }

        if (WIFEXITED(status)) 
        {
            printf("Child process %d terminated normally with exit status %d\n", terminated_pid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) 
        {
            printf("Child process %d terminated by signal %d\n", terminated_pid, WTERMSIG(status));
        }

        printf("Parent process finished\n");
        return 0;
    }
}