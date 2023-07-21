#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    char file_name[256];
    off_t offset;
    int file_descriptor;

    printf("Enter the file name: ");
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';

    printf("Enter the offset: ");
    scanf("%ld", &offset);

    file_descriptor = open(file_name, O_WRONLY);
    if (file_descriptor == -1) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

     if (ftruncate(file_descriptor, offset) == -1) 
     {
        perror("Error truncating file");
        exit(EXIT_FAILURE);
    }

    if (close(file_descriptor) == -1) 
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    printf("Data removed from offset %ld onwards in file %s\n", offset, file_name);

    return 0;
}