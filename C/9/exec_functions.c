#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    // Use execl() because you have the path to the program file.
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) {
        // If execl() returns -1, it failed.
        // Try to run ipconfig if ifconfig fails.
        if (execlp("ipconfig", "ipconfig", NULL) == -1) {
            // If execlp() also fails, print an error message.
            fprintf(stderr, "Cannot run ipconfig: %s\n", strerror(errno));
            return 1;
        }
    }

    return 0;
}
