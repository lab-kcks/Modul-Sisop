#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

int main()
{
    struct stat info;
    char path[100];
    int r;

    printf("Enter path to list files: ");
    scanf("%s", path);

    r = stat(path, &info);
    if( r==-1 )
    {
        fprintf(stderr,"File error\n");
        exit(1);
    }

    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);

    if (pw != 0) puts(pw->pw_name);
    if (gr != 0) puts(gr->gr_name);
}