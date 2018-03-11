#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int lstat(const char *__file, struct stat *__buf);

int main(int argc, char *argv[])
{
    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int s = lstat(argv[1],&sb);
    if(s != 0)
    {
        printf("lstat Error.\nExit Program.\nError Code: %d\n",s);
        return -1;
    }

    printf("------------------------ %s ------------------------\n",argv[1]);

    printf("   File type:                ");
    if(S_ISREG(sb.st_mode))
        printf("Regular File");
    else if(S_ISDIR(sb.st_mode))
        printf("Directory");
    else if(S_ISCHR(sb.st_mode))
        printf("Character device");
    else if(S_ISBLK(sb.st_mode))
        printf("Block device");
    else if(S_ISFIFO(sb.st_mode))
        printf("FIFO (named pipe)");
    else if(S_ISLNK(sb.st_mode))
        printf("Symbolic link");

    printf("\n   Access Privileges:        ");

printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");

    printf("\n   I-node number:            %ld\n", (long) sb.st_ino);
    printf("   Device number:            dev = %ld rdev = %ld\n",sb.st_dev,sb.st_rdev);
    printf("   Links count:              %ld\n",(long)sb.st_nlink);
    printf("   UID:                      %ld\n", (long) sb.st_uid);
    printf("   GID:                      %ld\n", (long) sb.st_gid);
    printf("   Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
    printf("   File size:                %lld bytes\n", (long long) sb.st_size);
    printf("   Blocks allocated:         %lld\n", (long long) sb.st_blocks);
    printf("   Last status change:       %s", ctime(&sb.st_ctime));
    printf("   Last file access:         %s", ctime(&sb.st_atime));
    printf("   Last inode change:        %s", ctime(&sb.st_mtime));

    return 0;
}
