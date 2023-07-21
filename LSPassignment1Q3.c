#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main() 
{
    char Fname[100];
    int access_mode;
    int fd = 0;

    printf("Enter the file name: ");
    scanf("%s",Fname);

    // Remove the newline character from the end of the file name
    Fname[strcspn(Fname, "\n")] = '\0';

    // Accept access mode from user
    printf("Enter the access mode (0 for read, 1 for write, 2 for execute): ");
    scanf("%d", &access_mode);

    // Open the file in the specified access mode
    fd  = open(Fname, access_mode);
    if (fd  == -1) 
    {
        perror("Error opening file");
        return -1;
    }

    printf("File is succesfully accesed with fd : %d\n",fd);

    close(fd);

    return 0;
}
