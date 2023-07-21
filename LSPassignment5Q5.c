#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() 
{
    char input_file_name[100];
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
        FILE* output_file;

        // Remove the newline character from the end of the buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // Create a new file with the same data
        strcpy(file_name, buffer);
        output_file = fopen(file_name, "w");
        if (output_file == NULL) 
        {
            perror("Error creating output file");
            continue;
        }

        // Write the data to the output file
        fprintf(output_file, "%s", buffer);

        // Close the output file
        fclose(output_file);
    }

    // Close the input file
    fclose(input_file);

    printf("Files created successfully.\n");

    return 0;
}