#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    char *argv[4] = {"ls", "-l", "/home", NULL};

    execv("/bin/ls", argv);

    // If execv returns, it means there was an error
    perror("Error executing ls");
    return EXIT_FAILURE;
}