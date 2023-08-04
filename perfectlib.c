#include <stdio.h>
#include "header.h"
int is_perfect(int n) 
{
    int sum = 0;

    for (int i = 1; i < n; i++) 
    {
        if (n % i == 0) 
        {
            sum += i;
        }
    }

    return (sum == n);
}

// To create .o file
// gcc -c -fPIC perfectlib.c

// To create .so file
// gcc -shared -o library.so perfectlib.o