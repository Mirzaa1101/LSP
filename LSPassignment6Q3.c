#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PATH_LENGTH 256

int main() 
{
    char directory_name[MAX_PATH_LENGTH];
    char file_name[MAX_PATH_LENGTH];
    char file_path[MAX_PATH_LENGTH];
    int file_descriptor;


    printf("Enter the directory name: ");
    fgets(directory_name, sizeof(directory_name), stdin);
    directory_name[strcspn(directory_name, "\n")] = '\0';


    printf("Enter the file name: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';


    snprintf(file_path, sizeof(file_path), "%s/%s", directory_name, file_name);


    file_descriptor = open(file_path, O_WRONLY | O_CREAT );
    if (file_descriptor == -1) 
    {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }


    if (close(file_descriptor) == -1) 
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    printf("File created successfully.\n");

    return 0;
}