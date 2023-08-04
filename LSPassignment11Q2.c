#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *thread_function(void *arg) 
{
    printf("Thread %ld started\n", pthread_self());

    // Perform thread operations here

    return NULL;
}

int main() 
{
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    printf("Creating threads\n");

    // Set thread attributes
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    struct sched_param param;
    param.sched_priority = 10;
    pthread_attr_setschedparam(&attr, &param);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        if (pthread_create(&threads[i], &attr, thread_function, NULL) != 0) 
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

    pthread_attr_destroy(&attr);

    printf("All threads completed\n");

    return 0;
}