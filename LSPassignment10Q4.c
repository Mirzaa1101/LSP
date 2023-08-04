#include <stdio.h>
#include <pthread.h>

// Structure to hold the data to be passed to the thread
typedef struct 
{
    int input;
    int output;
} ThreadData;

// Function to be executed in the thread
void *thread_function(void *arg) 
{
    ThreadData *data = (ThreadData *)arg;
    
    // Access the input value
    int input = data->input;
    
    // Perform operations using the input value
    int output = input * 2;
    
    // Store the output value in the data structure
    data->output = output;
    
    // Exit the thread
    pthread_exit(NULL);
}

int main() 
{
    pthread_t thread;
    
    // Create a structure to hold the thread data
    ThreadData data;
    
    // Get input value from the user
    printf("Enter a number: ");
    scanf("%d", &data.input);
    
    // Create the thread
    if (pthread_create(&thread, NULL, thread_function, (void *)&data) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }
    
    // Wait for the thread to complete
    pthread_join(thread, NULL);
    
    // Access the output value from the thread data
    int output = data.output;
    
    // Print the output value
    printf("Output: %d\n", output);
    
    return 0;
}