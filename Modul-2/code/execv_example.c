#include <stdio.h>
#include <unistd.h>

int main() {
    char *argv[4] = {"bin/ls", "-l", "/home", NULL};

    execv("/bin/ls", argv);

    // This line will not be executed if execv is successful
    printf("This line will not be executed\n");

    return 0;
}