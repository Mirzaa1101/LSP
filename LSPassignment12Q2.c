#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() 
{
    int shmid;
    key_t key;
    char *shm, *s;

    // Generate a unique key for shared memory
    key = ftok(".", 'x');

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) 
    {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process' address space
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) 
    {
        perror("shmat");
        exit(1);
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1)
     {
        perror("fork");
        exit(1);
    } 
    else if (pid == 0) 
    {
        // Child process
        printf("Child process writing to shared memory\n");

        // Write data to shared memory
        sprintf(shm, "Hello from the child process!");

        // Detach the shared memory segment from the child process' address space
        shmdt(shm);

        exit(0);
    } 
    else 
    {
        // Parent process
        wait(NULL);

        printf("Parent process reading from shared memory\n");

        // Read data from shared memory
        for (s = shm; *s != '\0'; s++) 
        {
            putchar(*s);
        }
        putchar('\n');

        // Detach the shared memory segment from the parent process' address space
        shmdt(shm);

        // Destroy the shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}