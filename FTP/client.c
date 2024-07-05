#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main() {
    FILE *fp;
    struct sockaddr_in sockAddr;
    int client;
    char name[1024], fname[1024], rcvg[1024];
    
    // Create socket
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket is created..\n");
    
    // Configure server address
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(6565);
    
    // Connect to server
    if (connect(client, (struct sockaddr *)&sockAddr, sizeof(sockAddr)) < 0) {
        perror("Connection failed");
        close(client);
        exit(EXIT_FAILURE);
    }
    printf("Connected....\n");
    
    // Get file name from user
    printf("Enter file name:\n");
    scanf("%s", name);
    
    // Get new file name for saving the content
    printf("Enter new file name:\n");
    scanf("%s", fname);
    
    // Open file for writing
    fp = fopen(fname, "wb");
    if (fp == NULL) {
        perror("File open failed");
        close(client);
        exit(EXIT_FAILURE);
    }
    
    // Send file name to server
    send(client, name, strlen(name), 0);
    
    while (1) {
        int s = recv(client, rcvg, sizeof(rcvg) - 1, 0);
        if (s < 0) {
            perror("Receive failed");
            fclose(fp);
            close(client);
            exit(EXIT_FAILURE);
        }
        rcvg[s] = '\0';
        
        if (strcmp(rcvg, "Error") == 0) {
            printf("File not available\n");
            fclose(fp);
            close(client);
            exit(EXIT_FAILURE);
        } else if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred..\n");
            fclose(fp);
            close(client);
            break;
        } else {
            fwrite(rcvg, 1, s, fp);
        }
    }
    
    return 0;
}
