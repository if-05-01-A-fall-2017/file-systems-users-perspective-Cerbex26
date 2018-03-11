#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int ftruncate(int __fd, __off_t __length);

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("./cpf <File 1> <File 2>\n");
        return -1;
    }

    int fd1 = open(argv[1],O_RDWR,S_IRUSR | S_IWUSR);
    
    if(fd1 < 0)
    {
        printf("File 1 Error.\nExit Program.\nError Code: %d\n",fd1);
        return -1;
    }

    int fd2 = open(argv[2],O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);

    ftruncate(fd2,0); 
    //Didn't know if I should just overwrite it or clear the content beforehand.

    if(fd2 < 0)
    {
        printf("File 2 Error.\nExit Program.\nError Code: %d\n",fd2);
        return -1;
    }

    char buf[1];
    int bytes_read = -1;
    while(bytes_read != 0)
    {
        bytes_read = read(fd1,buf,1);
        write(fd2,buf,1);
    }

    close(fd1);
    close(fd2);
    
    return 0;
 }