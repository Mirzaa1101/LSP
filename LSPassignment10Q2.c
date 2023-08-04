#include <stdio.h>
#include <pthread.h>

void *print_numbers_forward(void *arg) 
{
    for (int i = 1; i <= 500; i++) 
    {
        printf("%d\n", i);
    }

    return NULL;
}

void *print_numbers_backward(void *arg) 
{
    for (int i = 500; i >= 1; i--) 
    {
        printf("%d\n", i);
    }

    return NULL;
}

int main() 
{
    pthread_t thread1, thread2;

    printf("Creating threads\n");

    if (pthread_create(&thread1, NULL, print_numbers_forward, NULL) != 0) 
    {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_numbers_backward, NULL) != 0) 
    {
        perror("Failed to create thread 2");
        return 1;
    }

    printf("Threads created\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}