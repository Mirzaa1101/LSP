#include <stdio.h>
#include "arithmetic.h"
int addition(int a, int b) 
{
    return a + b;
}

int subtraction(int a, int b) 
{
    return a - b;
}

int multiplication(int a, int b) 
{
    return a * b;
}

float division(int a, int b) 
{
    return (float)a / b;
}

void __attribute__((constructor)) init() 
{
    printf("Arithmetic library loaded.\n");
}

void __attribute__((destructor)) cleanup() 
{
    printf("Arithmetic library unloaded.\n");
}

// To create .o file
// gcc -c -fPIC arithmic.c

// To create .so file
// gcc -shared -o library.so arithmic.o