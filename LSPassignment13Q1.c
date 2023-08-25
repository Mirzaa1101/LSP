#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_PATH "myfifo"
#define BUFFER_SIZE 256

int main() 
{
    int fd;
    pid_t pid;

    // Create the FIFO
    mkfifo(FIFO_PATH, 0666);

    // Create the child process
    pid = fork();

    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        // Child process (writer)
        char message[] = "Hello from the writer process!";

        // Open the FIFO for writing
        fd = open(FIFO_PATH, O_WRONLY);
        if (fd == -1) 
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Write the message to the FIFO
        if (write(fd, message, strlen(message) + 1) == -1) 
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the FIFO
        close(fd);

        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process (reader)
        char buffer[BUFFER_SIZE];

        // Open the FIFO for reading
        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) 
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Read the data from the FIFO
        if (read(fd, buffer, BUFFER_SIZE) == -1) 
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Received message: %s\n", buffer);

        // Close the FIFO
        close(fd);

        // Remove the FIFO
        unlink(FIFO_PATH);
    }

    return 0;
}