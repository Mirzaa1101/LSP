#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        close(pipefd[0]);  // Close the read end of the pipe
        
        char message[] = "Hello from the child process!";
        
        // Write the message to the pipe
        if (write(pipefd[1], message, sizeof(message)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        
        close(pipefd[1]);  // Close the write end of the pipe
        
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        close(pipefd[1]);  // Close the write end of the pipe
        
        // Read the data from the pipe
        ssize_t bytesRead = read(pipefd[0], buffer, BUFFER_SIZE);
        
        if (bytesRead == -1) 
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        printf("Parent process received: %.*s\n", (int)bytesRead, buffer);
        
        close(pipefd[0]);  // Close the read end of the pipe
        
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
