#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_SIZE 1024

int main() 
{
    int file_descriptor;
    off_t offset;

    file_descriptor = open("file.txt", O_WRONLY | O_CREAT );
    if (file_descriptor == -1) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    offset = lseek(file_descriptor, FILE_SIZE, SEEK_SET);
    if (offset == -1) 
    {
        perror("Error seeking file");
        exit(EXIT_FAILURE);
    }

    if (write(file_descriptor, "", 1) == -1) 
    {
        perror("Error writing file");
        exit(EXIT_FAILURE);
    }

    if (close(file_descriptor) == -1) 
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    printf("File with hole created successfully.\n");

    return 0;
}