#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket(const char *host, const char *port) {
    struct addrinfo *res;
    struct addrinfo hints;

    // Zero out the hints structure
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;       // Use either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;   // Use TCP for streaming

    // Resolve the address
    if (getaddrinfo(host, port, &hints, &res) != 0) {
        error("Can't resolve the address");
    }

    // Create the socket
    int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (d_sock == -1) {
        error("Can't open socket");
    }

    // Connect to the server
    if (connect(d_sock, res->ai_addr, res->ai_addrlen) == -1) {
        freeaddrinfo(res);
        error("Can't connect to socket");
    }

    freeaddrinfo(res);
    return d_sock;
}

int say(int socket, const char *s) {
    // Send data to the server
    int result = send(socket, s, strlen(s), 0);
    if (result == -1) {
        fprintf(stderr, "Error talking to the server: %s\n", strerror(errno));
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <search-term>\n", argv[0]);
        return 1;
    }

    // Open a connection to Wikipedia
    int d_sock = open_socket("en.wikipedia.org", "80");

    // Prepare the request string for the HTTP GET
    char buf[255];
    sprintf(buf, "GET /wiki/%s HTTP/1.1\r\n"
                 "Host: en.wikipedia.org\r\n"
                 "Connection: close\r\n\r\n", argv[1]);

    // Send the HTTP request to the server
    say(d_sock, buf);

    // Receive and print the response
    char rec[256];
    int bytesRcvd = recv(d_sock, rec, 255, 0);
    while (bytesRcvd > 0) {
        if (bytesRcvd == -1) {
            error("Can't read from server");
        }

        // Null-terminate the received data
        rec[bytesRcvd] = '\0';
        printf("%s", rec);

        // Receive the next chunk of data
        bytesRcvd = recv(d_sock, rec, 255, 0);
    }

    // Close the socket
    close(d_sock);
    return 0;
}
