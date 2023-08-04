#include "fileinfo.h"
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void displayFileInfo(const char* filename) 
{
    struct stat statbuf;

    if (stat(filename, &statbuf) == -1) 
    {
        perror("Failed to get file information");
        return;
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", statbuf.st_size);
    printf("Permissions: %o\n", statbuf.st_mode & 0777);
    printf("Last modified: %s", ctime(&statbuf.st_mtime));
}

// gcc -rdynamic -o Myexe client.c