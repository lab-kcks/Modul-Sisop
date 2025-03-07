#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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
        perror("Child: execv failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int child_status;
        printf("Parent waiting for child to complete...\n");
        wait(&child_status);
        
        if (WIFEXITED(child_status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(child_status));
            char *argv[3] = {"ls", "-l", NULL};
            printf("This is the parent process.\n");
            execv("/bin/ls", argv);
            perror("Parent: execv failed");
        } else if (WIFSIGNALED(child_status)) {
            printf("Child terminated by signal: %d\n", WTERMSIG(child_status));
        } else {
            printf("Child exited abnormally.\n");
        }
        exit(EXIT_FAILURE);
    }
}