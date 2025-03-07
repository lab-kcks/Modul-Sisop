#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    DIR *dp;
    struct dirent *ep;
    char path[100];

    // Allow user to enter a directory path
    printf("Enter path to list files (default: \"thisdir\"): ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }

    // Remove trailing newline if present
    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') {
        path[len - 1] = '\0';
    }

    // If no path was entered, use the default
    if (strlen(path) == 0) {
        strcpy(path, "thisdir");
    }

    dp = opendir(path);

    if (dp != NULL) {
        printf("Contents of directory '%s':\n", path);
        while ((ep = readdir(dp))) {
            printf("- %s\n", ep->d_name);
        }

        closedir(dp);
    } else {
        fprintf(stderr, "Couldn't open directory '%s': %s\n", path, strerror(errno));
        return 1;
    }

    return 0;
}