#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    char file_name[100];
    char string[100];


    printf("Enter the file name: ");
    fgets(file_name, sizeof(file_name), stdin);

    file_name[strcspn(file_name, "\n")] = '\0';

    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }


    printf("Enter the string to write in the file: ");
    fgets(string, sizeof(string), stdin);

   
    fputs(string, file);

    
    fclose(file);

    printf("String written to file successfully.\n");

    return 0;
}