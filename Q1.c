#include <stdio.h>
#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    void* handle = dlopen("./arithmetic.so", RTLD_LAZY);
    if (!handle) 
    {
        fprintf(stderr, "Failed to load the library: %s\n", dlerror());
        return 1;
    }

    int a = 10, b = 5;
    int (*add)(int, int) = dlsym(handle, "addition");
    int (*sub)(int, int) = dlsym(handle, "subtraction");
    int (*mul)(int, int) = dlsym(handle, "multiplication");
    float (*div)(int, int) = dlsym(handle, "division");

    printf("Addition: %d\n", add(a, b));
    printf("Subtraction: %d\n", sub(a, b));
    printf("Multiplication: %d\n", mul(a, b));
    printf("Division: %f\n", div(a, b));

    dlclose(handle);
    return 0;
}

// gcc -rdynamic -o Myexe Q1.c
// gcc -ldl -o Myexe client.c

// ./Myexe