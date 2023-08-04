#include <stdio.h>
#include "header.h"
int is_prime(int n) 
{
    if (n <= 1) 
    {
        return 0;
    }

    for (int i = 2; i * i <= n; i++) 
    {

        if (n % i == 0) 
        {
            return 0;
        }
    }

    return 1;
}

// To create .o file
// gcc -c -fPIC primelib.c

// To create .so file
// gcc -shared -o library.so primelib.o