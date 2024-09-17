#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

void error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void open_url(char *url)
{
    char launch[255];

    //This will open a web page on Windows.
    sprintf(launch, "cmd /c start %s", url);
    system(launch);
    //This will open a webpage on Linux.
    sprintf(launch, "x-www-browser '%s' &", url);
    system(launch);
    //This will open a webpage on mac
    sprintf(launch, "open '%s'", url);
    system(launch);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }

    char *phrase = argv[1];
    char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};

    // This array will store the descriptors for your pipe.
    int fd[2];

    // Create the pipe
    if (pipe(fd) == -1) {
        error("Can't create pipe");
    }

    // Fork the process
    pid_t pid = fork();
    if (pid == -1) {
        error("Can't fork process");
    }

    if (pid == 0) {
        // Child process
        // Close the read end of the pipe
        close(fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);

        // Close the write end of the pipe after duplicating
        close(fd[1]);

        // Execute the Python script with execle
        if (execle("/usr/bin/python", "/usr/bin/python", "./rssgossip.py",
                   "-u", phrase, NULL, vars) == -1) {
            error("Can't run script");
        }
    } else {
        // Parent process
        // Close the write end of the pipe
        close(fd[1]);

        // Read from the pipe
        char line[255];
        FILE *stream = fdopen(fd[0], "r");

        while (fgets(line, 255, stream)) {
            // If the line starts with a tab, it's a URL
            if (line[0] == '\t') {
                open_url(line + 1); // Open the URL, skipping the tab character
            }
        }

        // Close the read end
        close(fd[0]);
    }

    return 0;
}
