#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() 
{
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) 
    {
        // Parent process
        close(pipefd[0]);  // Close the read end of the pipe

        printf("Enter a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Write to the pipe
        write(pipefd[1], buffer, strlen(buffer) + 1);

        close(pipefd[1]);  // Close the write end of the pipe
    } 
    else 
    {
        // Child process
        close(pipefd[1]);  // Close the write end of the pipe

        // Read from the pipe
        read(pipefd[0], buffer, BUFFER_SIZE);

        printf("Received message: %s", buffer);

        close(pipefd[0]);  // Close the read end of the pipe
    }

    return 0;
}