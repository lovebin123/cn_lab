#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include<string.h>
int main() {
    int client;
    struct sockaddr_in clientAddr;
    char message[50];
    client=socket(AF_INET,SOCK_STREAM,0);
    if(client<0)
    {
        perror("Socket Creation failed");
        exit(EXIT_FAILURE);
    }

    clientAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    clientAddr.sin_port=htons(6265);
    clientAddr.sin_family=AF_INET;
       if(connect(client,(struct sockaddr *)&clientAddr,sizeof(clientAddr))<0)
   {
   printf("Error connecting cleint");
   exit(EXIT_FAILURE);
   }
    if(recv(client,message,sizeof(message),0)<0)
    {
        perror("Recieving failed");
        exit(EXIT_FAILURE);

    }
    printf("%s\n",message);
    int n;
    scanf("%d",&n);
    send(client,&n,sizeof(n),0);
    recv(client,message,sizeof(message),0);
    printf("%s",message);
    close(client);
}
