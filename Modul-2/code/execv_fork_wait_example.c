#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        printf("Error: Failed to fork\n");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        char *argv[4] = {"bin/ls", "-l", "/home", NULL};

        printf("This is child process.\n");
        execv("/bin/ls", argv);
    } else {
        int child_status;
        wait(&child_status);
        if (WIFEXITED(child_status)) {
            char *argv[3] = {"bin/ls", "-l", NULL};

            printf("This is parent process.\n");
            execv("/bin/ls", argv);
        } else {
            printf("Child process terminated.");
        }
        exit(0);
    }
}