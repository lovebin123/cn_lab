#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server, k = 5, m = 1, newSock, p;
    char buffer[1024];
    struct sockaddr_in servAddr, store;
    socklen_t addrSize = sizeof(servAddr);

    // Create socket
    server = socket(PF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Setup server address structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    // Bind socket
    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
        perror("Bind failed");
        close(server);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server, 5) == 0) {
        printf("Listening\n");
    } else {
        perror("Listen failed");
        close(server);
        exit(1);
    }

    // Accept a connection
    newSock = accept(server, (struct sockaddr *)&store, &addrSize);
    if (newSock == -1) {
        perror("Accept failed");
        close(server);
        exit(1);
    }

    // Communication loop
    while (k != 0) {
        int y = recv(newSock, buffer, sizeof(buffer), 0);
        if (y == -1) {
            perror("Receive failed");
            close(newSock);
            close(server);
            exit(1);
        }

        if (strncmp(buffer, "frame", 5) == 0) {
            printf("Received %d successfully\n", m);
        } else {
            printf("Frame %d was not received successfully\n", m);
        }

        if (m % 2 == 0) {
            strcpy(buffer, "ack");
        } else {
            strcpy(buffer, "kca");
            printf("Acknowledgement lost\n");
            for (p = 1; p <= 3; p++) {
                printf("Waiting for %d seconds\n", p);
                sleep(1);
            }
            printf("Sending ACk\n");
        }

        int z = send(newSock, buffer, strlen(buffer), 0);
        if (z == -1) {
            perror("Send failed");
            close(newSock);
            close(server);
            exit(1);
        }

        k--;
        m++;
    }

    // Close sockets
    close(newSock);
    close(server);

    return 0;
}
