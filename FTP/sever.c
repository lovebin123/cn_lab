#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int new_socket, valread, port;
    char *error_msg = "Error";
    char *completed_message = "completed";
    struct sockaddr_in sockAddr;
    int addrSize = sizeof(sockAddr);
    char buffer[1024] = {0};
    FILE *fp;

    printf("Enter port number: ");
    scanf("%d", &port);

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr *)&sockAddr, addrSize) < 0) {
        perror("Bind failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    if (listen(server, 3) < 0) {
        perror("Listen failed");
        close(server);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", port);

    while (1) {
        new_socket = accept(server, (struct sockaddr *)&sockAddr, (socklen_t *)&addrSize);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Connection established..\n");
        valread = read(new_socket, buffer, 1024);
        if (valread < 0) {
            perror("Read failed");
            send(new_socket, error_msg, strlen(error_msg), 0);
            close(new_socket);
            continue;
        }

        buffer[valread] = '\0';
        printf("Client requests file: %s\n", buffer);
        fp = fopen(buffer, "rb");
        if (fp == NULL) {
            perror("File open failed");
            send(new_socket, error_msg, strlen(error_msg), 0);
        } else {
            char file_buffer[1024];
            int bytes_read;
            while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), fp)) > 0) {
                send(new_socket, file_buffer, bytes_read, 0);
            }
            fclose(fp);
            send(new_socket, completed_message, strlen(completed_message), 0);
        }
        close(new_socket);
        printf("Session completed...Listening for new connection..\n");
    }

    close(server);
    return 0;
}
