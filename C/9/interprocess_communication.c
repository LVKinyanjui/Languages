#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    int pid_status;

    if (!pid) {
        puts("This is the child process");

        if (waitpid(pid, &pid_status, 0) == -1)
            fprintf(stderr, "Error waiting for the child process:\n%s\n", strerror(errno));
    }

    if (!WEXITSTATUS(pid_status))
        puts("This is the parent process");

    return 0;
}
