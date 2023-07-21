#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() 
{
    char source_file_name[100];
    char destination_file_name[100];
    int source_file = 0, destination_file = 0;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    printf("Enter the source file name: ");
    fgets(source_file_name, sizeof(source_file_name), stdin);


    source_file_name[strcspn(source_file_name, "\n")] = '\0';


    source_file = open(source_file_name, O_RDONLY);
    if (source_file == -1) 
    {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }


    printf("Enter the destination file name: ");
    fgets(destination_file_name, sizeof(destination_file_name), stdin);

 
    destination_file_name[strcspn(destination_file_name, "\n")] = '\0';


    destination_file = open(destination_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_file == -1) 
    {
        perror("Error creating destination file");
        exit(EXIT_FAILURE);
    }


    while ((bytes_read = read(source_file, buffer, BUFFER_SIZE)) > 0) 
    {
        bytes_written = write(destination_file, buffer, bytes_read);
        if (bytes_written != bytes_read) 
        {
            perror("Error writing to destination file");
            exit(EXIT_FAILURE);
        }
    }

  
    close(source_file);
    close(destination_file);

    printf("File copied successfully.\n");

    return 0;
}