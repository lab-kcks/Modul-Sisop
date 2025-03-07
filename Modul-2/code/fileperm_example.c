#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main()
{
    struct stat fs;
    char filename[100];
    int r;

    printf("Enter path to check file permissions: ");
    if (scanf("%99s", filename) != 1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    r = stat(filename, &fs);
    if (r == -1) {
        fprintf(stderr, "Error accessing '%s': %s\n", filename, strerror(errno));
        return EXIT_FAILURE;
    }

    printf("\nObtaining permission mode for '%s':\n", filename);

    printf("File type: ");
    if (S_ISREG(fs.st_mode))
        printf("Regular file\n");
    else if (S_ISDIR(fs.st_mode))
        printf("Directory\n");
    else if (S_ISLNK(fs.st_mode))
        printf("Symbolic link\n");
    else
        printf("Other\n");

    printf("Owner permissions: ");
    if (fs.st_mode & S_IRUSR)
        printf("read ");
    if (fs.st_mode & S_IWUSR)
        printf("write ");
    if (fs.st_mode & S_IXUSR)
        printf("execute");
    putchar('\n');

    printf("Group permissions: ");
    if (fs.st_mode & S_IRGRP)
        printf("read ");
    if (fs.st_mode & S_IWGRP)
        printf("write ");
    if (fs.st_mode & S_IXGRP)
        printf("execute");
    putchar('\n');

    printf("Others permissions: ");
    if (fs.st_mode & S_IROTH)
        printf("read ");
    if (fs.st_mode & S_IWOTH)
        printf("write ");
    if (fs.st_mode & S_IXOTH)
        printf("execute");
    putchar('\n');

    // Print numeric mode
    printf("Numeric mode: %o\n", fs.st_mode & 0777);

    return EXIT_SUCCESS;
}