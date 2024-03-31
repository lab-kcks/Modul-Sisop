#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_id;

    child_id = fork();

    if (child_id != 0) {
        printf("This is parent process.\nPID: %d", (int)getpid());
    } else {
        printf("\nThis is child process.\nPID: %d\n", child_id);
    }
}