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

    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGTERM, signal_handler);

    while (1) 
    {

        // Process loop
    }

    return 0;
}