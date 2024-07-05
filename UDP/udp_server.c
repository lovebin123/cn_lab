#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int server;
    char buffer[1000],buffer1[1000];
    struct sockaddr_in servAddr;
    struct sockaddr_in clientAddr;
    int client_addrlen=sizeof(clientAddr);
    server=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2002);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    printf("Binding is done\n");
    recvfrom(server,buffer1,1000,0,(struct sockaddr*)&clientAddr,&client_addrlen);
    printf("Message from cleint is:%s",buffer1);
    strcpy(buffer,"Hello I am server\n");
    sendto(server,buffer,1000,0,(struct sockaddr*)&servAddr,client_addrlen);
    close(server);


}