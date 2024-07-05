#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

int main() {
    int client, x, y, k = 5, m = 1, p;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize = sizeof(servAddr);

    // Create socket
    client = socket(PF_INET, SOCK_STREAM, 0);
    if (client == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Setup server address structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5600);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    // Connect to server
    y = connect(client, (struct sockaddr*)&servAddr, addrSize);
    if (y == -1) {
        perror("Connection failed");
        close(client);
        exit(1);
    }

    // Communication loop
    while (k != 0) {
        if (m <= 5) {
            printf("Sending data: %d\n", m);
        }

        if (m % 2 == 0) {
            strcpy(buffer, "frame");
        } else {
            strcpy(buffer, "error");
            printf("Packet Loss\n");
            for (p = 1; p <= 3; p++) {
                printf("Waiting for %d seconds\n", p);
                sleep(1);
         }
            printf("Retransmitting\n");
            strcpy(buffer, "frame");
        }

        // Send data to server
        x = send(client, buffer, strlen(buffer), 0);
        if (x == -1) {
            perror("Send failed");
            close(client);
            exit(1);
        } else {
            printf("Sent: %d\n", m);
        }

        // Receive acknowledgment from server
        int z = recv(client, buffer, sizeof(buffer), 0);
        if (z == -1) {
            perror("Receive failed");
            close(client);
            exit(1);
        }

        k--;
        m++;

        if (strncmp(buffer, "ack", 3) == 0) {
            printf("Ack received for %d\n", m - 1);
        } else {
            printf("Acknowledgement not received\n");
        }
    }

    // Close socket
    close(client);

    return 0;
}
