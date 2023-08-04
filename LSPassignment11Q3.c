#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2

int shared_data = 0;

void *thread_function(void *arg) 
{
    for (int i = 0; i < 10000; i++) 
    {
        shared_data++; // Increment the shared data
    }

    return NULL;
}

int main() 
{
    pthread_t threads[NUM_THREADS];

    printf("Creating threads\n");

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) 
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    printf("Threads created\n");

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        if (pthread_join(threads[i], NULL) != 0) 
        {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("Shared data: %d\n", shared_data);

    return 0;
}