#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() 
{
    char directory_name[20];

    printf("Enter the directory name: ");
    fgets(directory_name, sizeof(directory_name), stdin);

    directory_name[strcspn(directory_name, "\n")] = '\0';

    // Create the directory using the mkdir() system call
    if (mkdir(directory_name, 0777) == -1) 
    {
        perror("Error creating directory");
        exit(EXIT_FAILURE);
    }

    printf("Directory created successfully.\n");

    return 0;
}