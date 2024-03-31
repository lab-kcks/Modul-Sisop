#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Error: Failed to fork\n");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    if (setsid() < 0){
        perror("Error: setsid() failed");
    }

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        sleep(1);
    }
}