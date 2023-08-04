#include "fileinfo.h"
#include <stdio.h>

int main() 
{
    char filename[256];

    printf("Enter the filename: ");
    scanf("%s", filename);

    displayFileInfo(filename);

    return 0;
}

// gcc -static client.c -o Myexe sharedfile.a  

// ./Myexe

