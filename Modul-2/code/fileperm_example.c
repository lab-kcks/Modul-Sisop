#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    struct stat fs;
    char filename[100];
    int r;

    printf("Enter path to list files: ");
    scanf("%s", filename);

    r = stat(filename,&fs);
    if( r==-1 )
    {
        fprintf(stderr,"File error\n");
        exit(1);
    }

    printf("Obtaining permission mode for '%s':\n",filename);

    if( S_ISREG(fs.st_mode) )
        puts("Regular file");
    else
        puts("Not a regular file");

    printf("Owner permissions: ");
    if( fs.st_mode & S_IRUSR )
        printf("read ");
    if( fs.st_mode & S_IWUSR )
        printf("write ");
    if( fs.st_mode & S_IXUSR )
        printf("execute");
    putchar('\n');

    printf("Group permissions: ");
    if( fs.st_mode & S_IRGRP )
        printf("read ");
    if( fs.st_mode & S_IWGRP )
        printf("write ");
    if( fs.st_mode & S_IXGRP )
        printf("execute");
    putchar('\n');

    printf("Others permissions: ");
    if( fs.st_mode & S_IROTH )
        printf("read ");
    if( fs.st_mode & S_IWOTH )
        printf("write ");
    if( fs.st_mode & S_IXOTH )
        printf("execute");
    putchar('\n');

    return 0;
}