#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main()
{
    char input_file_name[20];
    char buffer[BUFFER_SIZE];
    FILE* input_file;

    printf("Enter the input file name: ");
    fgets(input_file_name, sizeof(input_file_name), stdin);
    input_file_name[strcspn(input_file_name, "\n")] = '\0';

    input_file = fopen(input_file_name, "r");
    if (input_file == NULL) 
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }


    while (fgets(buffer, sizeof(buffer), input_file) != NULL) 
    {
        char file_name[100];
        struct stat file_stat;

        buffer[strcspn(buffer, "\n")] = '\0';


        if (stat(buffer, &file_stat) == -1) 
        {
            perror("Error getting file status");
            continue;
        }

        if (file_stat.st_size > 10) 
        {
            printf("%s\n", buffer);
        }
    }

    fclose(input_file);

    return 0;
}
