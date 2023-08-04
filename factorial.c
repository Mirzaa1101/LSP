#include <stdio.h>
#include <stdio.h>
#include <dlfcn.h>

int main() 
{
    void* prime_handle = dlopen("./library1.so", RTLD_LAZY);
    if (!prime_handle) 
    {
        fprintf(stderr, "Failed to load the prime library: %s\n", dlerror());
        return 1;
    }

    void* perfect_handle = dlopen("./library1.so", RTLD_LAZY);
    if (!perfect_handle) 
    {
        fprintf(stderr, "Failed to load the perfect library: %s\n", dlerror());
        return 1;
    }

    int (*is_prime)(int) = dlsym(prime_handle, "is_prime");
    int (*is_perfect)(int) = dlsym(perfect_handle, "is_perfect");

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (is_prime(num)) 
    {
        printf("%d is prime.\n", num);
    } 
    else 
    {
        printf("%d is not prime.\n", num);
    }

    if (is_perfect(num)) 
    {
        printf("%d is perfect.\n", num);
    } 
    else 
    {
        printf("%d is not perfect.\n", num);
    }

    dlclose(prime_handle);
    dlclose(perfect_handle);

    return 0;
}

// To create .o file
// gcc -c -fPIC factorial.c

// To create .so file
// gcc -shared -o library.so factorial.o