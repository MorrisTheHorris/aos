// AOS Autumn 2019 - Report 2
// University of Tokyo
// Harrison Scott 2019/10/11
// This code forks and then prints out the VMA information of the child process

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_PATH 17 // based on pids being at most 5 digits

int main(void) {
    // Create a new process
    pid_t pid = fork();

    // Following code runs in parent process
    if (pid) {
        char path[MAX_PATH];
        char buf[BUFSIZ];
        int nbytes;

        // Create string containing the VMA path from procfs
        snprintf(path, MAX_PATH, "/proc/%d/maps", pid);

        // Print the contents of the file to stdout
        int fd = open(path, O_RDONLY);
        while ((nbytes = read(fd, buf, BUFSIZ)) > 0) {
            write(1, buf, nbytes);
        }
        close(fd);
    }

    return 0;
}