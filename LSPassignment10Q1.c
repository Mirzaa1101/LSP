#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) 
{
    printf("Thread is running\n");
    
    // Perform thread operations here
    
    return NULL;
}

int main() 
{
    pthread_t thread;

    printf("Creating thread\n");

    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }

    printf("Thread created\n");

    // Perform main thread operations here

    pthread_join(thread, NULL);

    return 0;
}