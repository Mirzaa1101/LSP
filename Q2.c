#include <stdio.h>
#include <stdio.h>
#include <dlfcn.h>


int main() 
{
    void* handle = dlopen("./library.so", RTLD_LAZY);
    if (!handle) 
    {
        fprintf(stderr, "Failed to load the library: %s\n", dlerror());
        return 1;
    }

    int (*compare)(const char*, const char*) = dlsym(handle, "compare_files");

    char file1[100], file2[100];
    printf("Enter the first file name: ");
    scanf("%s", file1);
    printf("Enter the second file name: ");
    scanf("%s", file2);

    int result = compare(file1, file2);
    if (result == -1) 
    {
        printf("Failed to open files.\n");
    } 
    else if (result == 1) 
    {
        printf("Files are identical.\n");
    } 
    else 
    {
        printf("Files are different.\n");
    }

    dlclose(handle);
    return 0;
}

// gcc -rdynamic -o Myexe Q2.c
// gcc -ldl -o Myexe Q2.c

// ./Myexe