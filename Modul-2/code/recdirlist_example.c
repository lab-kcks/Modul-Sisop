#include <stdio.h>
#include <string.h>
#include <dirent.h>

void listFilesRecursively(char *path);

int main()
{
    char path[100] = "thisdir";

    listFilesRecursively(path);

    return 0;
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            printf("%s\n", path);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}