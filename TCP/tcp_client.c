#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
int client;
char buffer[1024];
struct sockaddr_in servAddr;
socklen_t addrSize;
client=socket(AF_INET,SOCK_STREAM,0);
servAddr.sin_family=AF_INET;
servAddr.sin_port=htons(6265);
servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(client,(struct sockaddr *)&servAddr,sizeof(servAddr));
printf("Sending data to server");
strcpy(buffer,"Hi this is client");
send(client,buffer,19,0);
recv(client,buffer,1024,0);
printf("Data recieved is:%s",buffer);
close(client);
}
