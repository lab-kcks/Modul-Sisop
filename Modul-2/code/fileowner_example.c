#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main()
{
    struct stat info;
    char path[100];
    int r;

    printf("Enter path to check file ownership: ");
    if (scanf("%99s", path) != 1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    r = stat(path, &info);
    if (r == -1) {
        fprintf(stderr, "Error accessing '%s': %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    struct passwd *pw = getpwuid(info.st_uid);
    struct group *gr = getgrgid(info.st_gid);

    printf("\nFile ownership for '%s':\n", path);
    
    if (pw != NULL) {
        printf("Owner: %s (UID: %d)\n", pw->pw_name, (int)info.st_uid);
    } else {
        printf("Owner: Unknown (UID: %d)\n", (int)info.st_uid);
    }
    
    if (gr != NULL) {
        printf("Group: %s (GID: %d)\n", gr->gr_name, (int)info.st_gid);
    } else {
        printf("Group: Unknown (GID: %d)\n", (int)info.st_gid);
    }

    return EXIT_SUCCESS;
}