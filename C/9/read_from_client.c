#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int listener_d;

// Error handling function
void error(char *msg) {
    // Display the error message and system error string
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    // Stop the program
    exit(1);
}

// Function to open a listener socket
int open_listener_socket() {
    // Create an Internet streaming socket (TCP/IP)
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        error("Can't open socket");
    }
    // Return the socket descriptor
    return s;
}

// Function to bind the socket to a port
void bind_to_port(int socket, int port) {
    // Structure to hold the address and port
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);  // Assign port number
    name.sin_addr.s_addr = htonl(INADDR_ANY);  // Bind to any available interface

    // Allow socket reuse
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        error("Can't set the reuse option on the socket");
    }

    // Bind the socket to the address and port
    int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (c == -1) {
        error("Can't bind to socket");
    }
}

// Function to send a message to the client
int say(int socket, char *s) {
    // Send a string to the client
    int result = send(socket, s, strlen(s), 0);
    if (result == -1) {
        // Print error but don't stop the server
        fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
    }
    // Return the result of the send operation
    return result;
}

int read_in(int socket, char *buf, int len) {
    // Pointer to keep track of the current position in the buffer
    char *s = buf;
    // Remaining length of the buffer to fill
    int slen = len;
    // Read characters from the socket
    int c = recv(socket, s, slen, 0);

    // Keep reading until we either reach the end of data or a newline character
    while ((c > 0) && (s[c - 1] != '\n')) {
        s += c;        // Move the buffer pointer forward
        slen -= c;     // Decrease the remaining length
        c = recv(socket, s, slen, 0);  // Read more data from the socket
    }

    // Error handling for the read operation
    if (c < 0) {
        // If there was an error, return the error code
        return c;
    } else if (c == 0) {
        // If nothing was read, return an empty string
        buf[0] = '\0';
    } else {
        // Replace the last character (newline) with a null terminator
        s[c - 1] = '\0';
    }

    // Return the number of bytes read
    return len - slen;
}

void handle_interrupt(int sig)
{
    if (listener_d)
        close(listener_d);

    perror("Server closed. Byw!");
    exit(1);                // Very important
}


int catch_signal(int sig, void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    return sigaction(sig, &action, NULL);
}

int main(int argc, char *argv[]) {
    // Set up the signal handler for SIGINT (Ctrl-C)
    if (catch_signal(SIGINT, handle_interrupt) == -1)
        error("Can't set the interrupt handler");

    // Create a listener socket on port 30000
    listener_d = open_listener_socket();
    bind_to_port(listener_d, 30000);

    // Set the listen-queue length to 10
    if (listen(listener_d, 10) == -1)
        error("Can't listen");

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    char buf[255];

    puts("Waiting for connection");

    // Main server loop: listen for connections and handle requests
    while (1) {
        // Accept an incoming connection
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1)
            error("Can't open secondary socket");

        int pid = fork();
        if (!pid){
            close(listener_d);
            // Send greeting message to the client
            if (say(connect_d, "Internet Knock-Knock Protocol Server\r\nVersion 1.0\r\nKnock! Knock!\r\n> ") != -1) {
                // Read client's response
                read_in(connect_d, buf, sizeof(buf));

                // Check if client asked "Who's there?"
                if (strncasecmp("Who's there?", buf, 12)) {
                    say(connect_d, "You should say 'Who's there?'!\r\n");
                } else {
                    // Send second knock-knock joke line
                    if (say(connect_d, "Oscar\r\n> ") != -1) {
                        // Read client's response
                        read_in(connect_d, buf, sizeof(buf));

                        // Check if client asked "Oscar who?"
                        if (strncasecmp("Oscar who?", buf, 10)) {
                            say(connect_d, "You should say 'Oscar who?'!\r\n");
                        } else {
                            // Send punchline
                            say(connect_d, "Oscar silly question, you get a silly answer!\r\n");
                        }
                    }
                }
            }

            // Close the connection with the client
            close(connect_d);
            exit(0);
        }
        close(connect_d);
}
    return 0;
}
