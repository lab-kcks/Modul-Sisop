#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

void listFilesRecursively(char *path, int depth);

int main()
{
    char path[100];

    // Allow user to enter a directory path
    printf("Enter path to list files recursively (default: \"thisdir\"): ");
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

    printf("Recursive listing of directory '%s':\n", path);
    listFilesRecursively(path, 0);

    return 0;
}

// Recursively list files with indentation based on depth
void listFilesRecursively(char *basePath, int depth)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir) {
        fprintf(stderr, "Cannot open directory '%s': %s\n", basePath, strerror(errno));
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // Print indentation based on depth
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            
            printf("|-- %s\n", dp->d_name);

            // Construct new path
            snprintf(path, sizeof(path), "%s/%s", basePath, dp->d_name);
            
            // Recursively list subdirectories
            listFilesRecursively(path, depth + 1);
        }
    }

    closedir(dir);
}