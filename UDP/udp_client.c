#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
    int client;
    char buffer[1000],buffer1[1000];
    struct sockaddr_in servAddr;
    int server_struct_length=sizeof(servAddr);
    client=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2002);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    strcpy(buffer,"This is from UDP client\n");
    sendto(client,buffer,24,0,(struct sockaddr*)&servAddr,sizeof(servAddr));
    recvfrom(client,buffer1,1000,0,(struct sockaddr *)&servAddr,&server_struct_length);
    printf("Message from server is:%s",buffer1);
    close(client);
}