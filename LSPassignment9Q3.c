#include <stdio.h>
#include <sys/resource.h>

int main()
{
    pid_t pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);
    
    if (priority == -1) 
    {
        perror("Failed to get priority");
        return 1;
    }

    printf("Process priority: %d\n", priority);

    return 0;
}