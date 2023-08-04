#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

pthread_mutex_t mutex;
pthread_cond_t cond;
int count = 0;

void *thread_function(void *arg) 
{
    int thread_num = *(int *)arg;

    printf("Thread %d started\n", thread_num);

    // Perform thread operations here

    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);

    // Signal main thread if all threads have completed
    if (count == NUM_THREADS) 
    {
        pthread_cond_signal(&cond);
    }

    printf("Thread %d finished\n", thread_num);

    return NULL;
}

int main() 
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    printf("Creating threads\n");

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) 
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    pthread_mutex_lock(&mutex);

    // Wait until all threads have completed
    while (count < NUM_THREADS) 
    {
        pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);

    printf("All threads completed\n");

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}