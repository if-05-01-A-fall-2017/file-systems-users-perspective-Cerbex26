#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 

#define S_IFSOCK __S_IFSOCK

int lstat(const char *__file, struct stat *__buf);

int main(int argc, char *argv[])
{
    struct stat sb;
    DIR *d;
    struct dirent *dir;
    if(argc == 1)
        d = opendir(".");
    else if(argc == 2)
        d = opendir(argv[1]);
        
    while((dir = readdir(d)) != NULL)
    {
        if(dir->d_name[0] == '.')
        {
            continue;
        }
        int s = lstat(dir->d_name,&sb);
        if(s != 0)
        {
            printf("lstat Error.\nExit Program.\nError Code: %d\n",s);
            return -1;
        }

        if(S_ISREG(sb.st_mode))
            printf("-");
        else if(S_ISDIR(sb.st_mode))
            printf("d");
        else if(S_ISCHR(sb.st_mode))
            printf("c");
        else if(S_ISBLK(sb.st_mode))
            printf("b");
        else if(S_ISFIFO(sb.st_mode))
            printf("f");
        else if(S_ISLNK(sb.st_mode))
            printf("l");
        else if(S_IFSOCK & sb.st_mode)
            printf("s");

        printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
        printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
        printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
        printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
        printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
        printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
        printf( (sb.st_mode & S_IROTH) ? "r" : "-");
        printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
        printf( (sb.st_mode & S_IXOTH) ? "x" : "-");

        printf(" %-5d %-5d",sb.st_uid,sb.st_gid);
        printf(" %-9lld",(long long)sb.st_size);
        char buf[70];
        strftime(buf,sizeof buf,"%Y-%m-%d-%H-%M",localtime(&sb.st_mtime));
        printf(" %s",buf);
        printf(" %s\n",dir->d_name);
    }
    closedir(d);
}