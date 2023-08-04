#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int countCapitalChars(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Failed to open file");
        exit(1);
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (ch >= 'A' && ch <= 'Z') 
        {
            count++;
        }
    }

    fclose(file);
    return count;
}

int main() 
{
    pid_t pid1, pid2;
    int status;

    // Process 1
    pid1 = fork();

    if (pid1 == -1) 
    {
        perror("Failed to create Process 1");
        return 1;
    }

    if (pid1 == 0) 
    {
        // Child Process 1
        int count = countCapitalChars("demo.txt");

        int countFile = open("count.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (countFile < 0) 
        {
            perror("Failed to open count.txt");
            exit(1);
        }

        dprintf(countFile, "Process 1: Count = %d\n", count);

        close(countFile);
        exit(0);
    } 
    else 
    {
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
            int count = countCapitalChars("hello.txt");

            int countFile = open("count.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (countFile < 0) 
            {
                perror("Failed to open count.txt");
                exit(1);
            }

            dprintf(countFile, "Process 2: Count = %d\n", count);

            close(countFile);
            exit(0);
        }
    }

    // Parent process waits for both child processes to terminate
    waitpid(pid1, &status, 0);
    printf("Process 1 terminated\n");

    waitpid(pid2, &status, 0);
    printf("Process 2 terminated\n");

    printf("Parent process terminated\n");

    return 0;
}