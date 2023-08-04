#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main() 
{
    printf("Before yielding the processor\n");

    if (sched_yield() == -1) 
    {
        perror("Failed to yield the processor");
        return 1;
    }

    printf("After yielding the processor\n");

    return 0;
}