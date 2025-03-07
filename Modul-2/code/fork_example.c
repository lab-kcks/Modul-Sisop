#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child_id;

    child_id = fork();

    if (child_id < 0) {
        // Fork failed
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (child_id != 0) {
        // Parent process
        printf("This is the parent process.\nPID: %d, Child's PID: %d\n", (int)getpid(), (int)child_id);
    } else {
        // Child process
        printf("This is the child process.\nPID: %d, Parent's PID: %d\n", (int)getpid(), (int)getppid());
    }
    
    return EXIT_SUCCESS;
}