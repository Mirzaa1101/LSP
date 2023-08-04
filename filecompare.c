#include <stdio.h>
#include "filecompare.h"
int compare_files(const char* file1, const char* file2) 
{
    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) 
    {
        perror("Failed to open files");
        return -1;
    }

    int c1, c2;
    while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) 
    {
        if (c1 != c2) 
        {

            fclose(f1);
            fclose(f2);
            return 0; // Files are different
        }
    }

    int eof1 = feof(f1);
    int eof2 = feof(f2);

    fclose(f1);
    fclose(f2);

    if (eof1 && eof2) 
    {
        return 1; // Files are identical
    } 
    else 
    {
        return 0; // Files are different
    }
}
// To create .o file
// gcc -c -fPIC filecompare.c

// To create .so file
// gcc -shared -o library.so filecompare.o