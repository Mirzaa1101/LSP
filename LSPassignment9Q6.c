#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main() 
{
    char **env = environ;
    
    printf("Environment variables:\n");
    
    while (*env) 
    {
        printf("%s\n", *env);
        env++;
    }
    
    return 0;
}
