#include<stdio.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
    char Fname[30];
    int fd = 0;
    
    printf("Enter name of file : \n");
    scanf("%s",Fname);

    fd = open(Fname, O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open file\n");
        return -1;
    }
    else
    {
        printf("File is succesfully opened with fd : %d\n",fd);
    }

    return 0;
}
