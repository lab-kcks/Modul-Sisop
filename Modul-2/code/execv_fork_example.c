#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        char *argv[4] = {"bin/ls", "-l", "/home", NULL};

        printf("This is child process.\n");
        execv("/bin/ls", argv);
    } else {
        char *argv[3] = {"bin/ls", "-l", NULL};

        printf("This is parent process.\n");
        execv("/bin/ls", argv);
    }
}