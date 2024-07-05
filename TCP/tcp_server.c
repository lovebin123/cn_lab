#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
void main()
{
    int server,newSock;
    char buffer[1000];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
   socklen_t addrSize;
    server=socket(AF_INET,SOCK_STREAM,0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6265);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));
    if(listen(server,5)==0)
    printf("Listening");
    else
    printf("Error");
    newSock=accept(server,(struct sockaddr*)&store,&addrSize);
    recv(newSock,buffer,1024,0);
    printf("Data recieved is:%s",buffer);
    strcpy(buffer,"Hi this is server");
    send(newSock,buffer,19,0);
    close(newSock);
    close(server);



}