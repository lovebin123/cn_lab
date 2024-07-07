#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

bool check(int n) {
    if (n <= 1) return false; // 0 and 1 are not prime numbers
    if (n % 2 == 0) return (n == 2); // Even numbers greater than 2 are not prime
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize = sizeof(store);
    int server, client;
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_port=htons(6265);
    servAddr.sin_family=AF_INET;
    if(server<0)
    {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
    if(bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr))<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if(listen(server,5)<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    printf("Listening\n");
    client=accept(server,(struct sockaddr *)&store,&addrSize);
    if(client<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    char buffer[1000]="Enter an integer";
    send(client,buffer,strlen(buffer),0);
    int n;
    if((recv(client,&n,sizeof(n),0))<0)
    {
    perror("Error");
    exit(EXIT_FAILURE);
    }
    printf("Recieved message from Client\n");
    bool k=check(n);
    if(k)
    {
        send(client,"Number is Prime",strlen("Number is Prime"),0);
    }
    else{
        send(client,"Number is not prime",strlen("Number is not prime"),0);
    }
    close(server);
    close(client);

}
