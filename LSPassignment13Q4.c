#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal_number) 
{
    printf("Received signal: %d\n", signal_number);
}

int main() 
{
    int signal_number;
    printf("Enter the signal number: ");
    scanf("%d", &signal_number);

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(signal_number, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) 
    {
        // Process loop
    }

    return 0;
}