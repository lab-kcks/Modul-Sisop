#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        char *argv[4] = {"ls", "-l", "/home", NULL};
        printf("This is the child process.\n");
        execv("/bin/ls", argv);
        // This line executes only if execv fails
        perror("Child: execv failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        char *argv[3] = {"ls", "-l", NULL};
        printf("This is the parent process.\n");
        execv("/bin/ls", argv);
        // This line executes only if execv fails
        perror("Parent: execv failed");
        exit(EXIT_FAILURE);
    }
}