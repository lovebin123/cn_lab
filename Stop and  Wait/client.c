#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
int main()
{
    int client,k=5,m=1;
    struct sockaddr_in servAddr;
    char buffer[1024];
    socklen_t addrSize=sizeof(servAddr);
    client=socket(AF_INET,SOCK_STREAM,0);
    if(client<0)
    {
        perror("Error client");
        exit(EXIT_FAILURE);
    }
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5655);
    if(connect(client,(struct sockaddr *)&servAddr,addrSize)<0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    while(k!=0)
    {
        if(m<=5)
        {
            printf("Sending %d data\n",m);
        }
        if(m%2==0)
        {
            strcpy(buffer,"frame");
        }
        else{
            strcpy(buffer,"error");
            for(int i=1;i<=3;i++)
            {
                printf("Waiting for %d seconds",i);
                sleep(1);
            }
            printf("Retransmitting\n");
            strcpy(buffer,"frame");
        }
        int x=send(client,buffer,sizeof(buffer),0);
        if(x<0)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        else{
            printf("Sent %d\n",m);
        }
        int y=recv(client,buffer,sizeof(buffer),0);
        if(y<0)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
        k--;
        m++;
        if(strncmp(buffer,"ack",3)==0)
        {
            printf("Acknowledgement recieved for:%d\n",m);
        }
        else{
            printf("Acknowledgement not recieved\n");
        }
    }
    close(client);
}