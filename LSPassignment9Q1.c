#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() 
{
    pid_t pid;
    FILE* file;

    // Fork off the parent process
    pid = fork();

    // An error occurred
    if (pid < 0) 
    {
        perror("Failed to fork");
        exit(1);
    }

    // Success: Let the parent terminate
    if (pid > 0) 
    {
        printf("Parent process terminated\n");
        exit(0);
    }

    // On success: The child process writes file names to "demo.txt"
    file = fopen("demo.txt", "w");
    if (file == NULL) 
    {
        perror("Failed to open demo.txt");
        exit(1);
    }

    // Change the current working directory to the desktop
    if (chdir("/path/to/desktop") < 0) 
    {
        perror("Failed to change directory to desktop");
        exit(1);
    }

    // Read all file names on the desktop
    DIR* dir;
    struct dirent* entry;

    dir = opendir(".");
    if (dir == NULL) 
    {
        perror("Failed to open directory");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_REG) 
        {  // Only process regular files
            fprintf(file, "%s\n", entry->d_name);
        }
    }

    closedir(dir);
    fclose(file);

    printf("Child process completed\n");

    return 0;
}