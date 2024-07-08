#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
int  main()
{
    int server,client;
    int k=5,m=1;
    server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr,clientAddr;
    char buffer[1024];
    socklen_t addrSize=sizeof(servAddr);
    if(server<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(5655);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr))<0)
    {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    if(listen(server,5)<0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    printf("Listening\n");
    client=accept(server,(struct sockaddr *)&clientAddr,&addrSize);
    if(client<0)
    {
        perror("Error creating clinet");
        exit(EXIT_FAILURE);
    }
    while(k!=0)
    {
        int s=recv(client,buffer,1024,0);
        if(s<0)
        {
            perror("Error reciving");
            exit(EXIT_FAILURE);
        }
        if(strncmp(buffer,"frame",3)==0)
        {
            printf("Acknowledgement recieved for:%d\n",m);
        }
        else{
            printf("Acknowledgement failed for:%d\n",m);
        }
        if(m%2==0)
        strcpy(buffer,"ack");
        else{
            strcpy(buffer,"kca");
            for(int i=1;i<=3;i++)
            {
                printf("Waiting for %d seconds\n",i);
                sleep(1);
            }
            printf("Retransmitting\n");
            strcpy(buffer,"ack");
        }
        printf("Sending acknowlegemnt\n");
        if((send(client,buffer,strlen(buffer),0)<0))
        {
            perror("Error Sending");
            exit(EXIT_FAILURE);
        }
        k--;
        m++;

    }
}