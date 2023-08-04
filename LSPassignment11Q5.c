#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

#define BUFFER_SIZE 256

int capital_count = 0;
int small_count = 0;

void *count_capital(void *arg) 
{
    FILE *file = fopen("demo.txt", "r");
    if (file == NULL) 
    {
        perror("Failed to open file");
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
    {
        for (int i = 0; buffer[i] != '\0'; i++) 
        {
            if (isupper(buffer[i])) 
            {
                capital_count++;
            }
        }
    }

    fclose(file);
    return NULL;
}

void *count_small(void *arg) 
{
    FILE *file = fopen("demo.txt", "r");
    if (file == NULL) 
    {
        perror("Failed to open file");
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) 
    {
        for (int i = 0; buffer[i] != '\0'; i++) 
        {
            if (islower(buffer[i])) 
            {
                small_count++;
            }
        }
    }

    fclose(file);
    return NULL;
}

int main() 
{
    pthread_t capital_thread, small_thread;

    if (pthread_create(&capital_thread, NULL, count_capital, NULL) != 0) 
    {
        perror("Failed to create capital thread");
        return 1;
    }

    if (pthread_create(&small_thread, NULL, count_small, NULL) != 0) 
    {
        perror("Failed to create small thread");
        return 1;
    }

    if (pthread_join(capital_thread, NULL) != 0) 
    {
        perror("Failed to join capital thread");
        return 1;
    }

    if (pthread_join(small_thread, NULL) != 0) 
    {
        perror("Failed to join small thread");
        return 1;
    }

    printf("Number of capital characters: %d\n", capital_count);
    printf("Number of small characters: %d\n", small_count);

    return 0;
}