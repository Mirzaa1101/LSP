#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/stat.h>

#define BUFFER_SIZE 10

int main() 
{
    char directory_name[20];
    char output_file_name[] = "Demo.txt";
    DIR* directory;
    struct dirent* entry;
    int output_file;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    int file_count = 0;


    printf("Enter the directory name: ");
    fgets(directory_name, sizeof(directory_name), stdin);

    directory_name[strcspn(directory_name, "\n")] = '\0';

    directory = opendir(directory_name);
    if (directory == NULL) 
    {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }


    output_file = open(output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_file == -1) 
    {
        perror("Error creating output file");
        exit(EXIT_FAILURE);
    }

    // Read each entry in the directory
    while ((entry = readdir(directory)) != NULL) 
    {
        char file_path[200];
        struct stat file_stat;

        // Create the file path by concatenating the directory name and entry name
        snprintf(file_path, sizeof(file_path), "%s/%s", directory_name, entry->d_name);

        // Get the file status
        if (stat(file_path, &file_stat) == -1) 
        {
            perror("Error getting file status");
            continue;
        }

        // Check if the entry is a regular file
        if (S_ISREG(file_stat.st_mode)) 
        {
            int input_file;
            file_count++;

            // Open the input file for reading
            input_file = open(file_path, O_RDONLY);
            if (input_file == -1) 
            {
                perror("Error opening input file");
                continue;
            }

            // Read the first 10 bytes from the input file
            bytes_read = read(input_file, buffer, BUFFER_SIZE);
            if (bytes_read == -1) 
            {
                perror("Error reading from input file");
                close(input_file);
                continue;
            }

            // Write the bytes to the output file
            bytes_written = write(output_file, buffer, bytes_read);
            if (bytes_written == -1) 
            {
                perror("Error writing to output file");
                close(input_file);
                continue;
            }

            close(input_file);
        }
    }


    closedir(directory);


    close(output_file);

    printf("Copied first 10 bytes from %d regular files to %s.\n", file_count, output_file_name);

    return 0;
}