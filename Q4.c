#include "factorial.h"
#include <stdio.h>

int main() 
{
    int n = 5;
    int result = factorial(n);
    printf("Factorial of %d is %d\n", n, result);
    return 0;
}

// gcc -rdynamic -o Myexe Q3.c
// gcc -ldl -o Myexe Q3.c

// ./Myexe