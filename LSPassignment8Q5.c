#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() 
{
    pid_t pid;

    // Fork off the parent process
    pid = fork();

    // An error occurred
    if (pid < 0) 
    {
        perror("Failed to fork");
        exit(1);
    }

    // Success: Let the parent terminate
    if (pid > 0) 
    {
        printf("Parent process terminated\n");
        exit(0);
    }

    // On success: The child process becomes the daemon
    umask(0); // Set the file mode mask

    // Create a new session ID for the child process
    if (setsid() < 0) 
    {
        perror("Failed to create new session");
        exit(1);
    }

    // Change the current working directory to root
    if (chdir("/") < 0) 
    {
        perror("Failed to change directory to /");
        exit(1);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Open a log file in write mode
    int log_fd = open("/var/log/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (log_fd < 0) 
    {
        perror("Failed to open log file");
        exit(1);
    }

    // Redirect standard file descriptors to the log file
    dup2(log_fd, STDIN_FILENO);
    dup2(log_fd, STDOUT_FILENO);
    dup2(log_fd, STDERR_FILENO);

    // Daemon process is now running

    // Run the daemon process logic
    while (1) 
    {
        // Do something...
        sleep(1);
    }

    return 0;
}