#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILE_PATH "example.txt"

int main() 
{
    int fd;
    struct stat sb;
    char *mapped_file;

    // Open the file
    fd = open(FILE_PATH, O_RDONLY);
    if (fd == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Get the file size
    if (fstat(fd, &sb) == -1) 
    {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    // Map the file into memory
    mapped_file = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (mapped_file == MAP_FAILED) 
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Read and print the data from the mapped file
    printf("Data from the mapped file:\n%s\n", mapped_file);

    // Unmap the file from memory
    if (munmap(mapped_file, sb.st_size) == -1) 
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) 
    {

        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}