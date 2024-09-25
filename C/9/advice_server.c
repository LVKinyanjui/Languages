#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void handle_interrupt(int sig)
{
    puts("Server closed.");
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
    char *advice[] = {
        "Take smaller bites\r\n",
        "Go for the tight jeans. No, they do NOT make you look fat.\r\n",
        "One word: inappropriate\r\n",
        "Just for today, be honest. Tell your boss what you *really* think\r\n",
        "You might want to rethink that haircut\r\n"
    };


    // Create a socket
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
        perror("Can't set the reuse option on the socket");

    if (listener_d == -1) {
        perror("Can't open socket");
        return 1;
    }

    // Configure the socket
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to port 30000
    if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1) {
        perror("Can't bind to port");
        return 1;
    }

    // Set the listen queue depth to 10
    if (listen(listener_d, 10) == -1) {
        perror("Can't listen");
        return 1;
    }

    puts("Waiting for connection");

    // Set up interrupt signal catching Ctrl + C
    // Optional
    catch_signal(SIGINT, handle_interrupt);

    // Loop to accept and handle connections
    while (1) {
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);

        if (connect_d == -1) {
            perror("Can't accept connection");
            continue;
        }

        // Select a random advice message
        char *msg = advice[rand() % 5];

        // Send the message to the client
        if (send(connect_d, msg, strlen(msg), 0) == -1) {
            perror("Can't send message");
        }

        // Close the connection to the client
        close(connect_d);
    }

    // Close the listener socket (not reachable in this loop)
    close(listener_d);

    return 0;
}
