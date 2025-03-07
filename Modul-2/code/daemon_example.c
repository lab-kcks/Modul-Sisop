#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
    // Step 1: Fork the parent process
    pid_t child_pid = fork();

    if (child_pid < 0) {
        // Fork failed
        perror("Error: Failed to fork");
        exit(EXIT_FAILURE);
    }

    // Step 2: Exit the parent process
    // This makes the child an orphan which will be adopted by init
    if (child_pid > 0) {
        printf("Daemon process started with PID: %d\n", child_pid);
        exit(EXIT_SUCCESS);
    }

    // Step 3: Set file mode creation mask
    // This gives the daemon permission to read/write files it creates
    umask(0);

    // Step 4: Create a unique Session ID
    // This prevents the child from becoming an orphan
    pid_t sid = setsid();
    if (sid < 0) {
        perror("Error: setsid() failed");
        exit(EXIT_FAILURE);
    }

    // Step 5: Change working directory to root
    // This ensures daemon won't lock any directories
    if (chdir("/") < 0) {
        perror("Error: chdir() failed");
        exit(EXIT_FAILURE);
    }

    // Step 6: Close standard file descriptors
    // Daemons shouldn't use the terminal
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Daemon main loop
    while (1) {
        // Here we would put the daemon's actual work
        // For example, we could write a timestamp to a log file
        
        // Example: Log current time every second
        time_t now = time(NULL);
        syslog(LOG_INFO, "Daemon running at: %s", ctime(&now));
        
        sleep(1);
    }
    return EXIT_SUCCESS;
}