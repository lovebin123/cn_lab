#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<sys/types.h>
#include<sys/time.h>
#include<fcntl.h>
void rsend(int ch,int c_sock)
{
    char buff[1000];
    bzero(buff,sizeof(buff));
    strcpy(buff,"Retransmission Message");
    buff[strlen(buff)]=(ch)+'0';
    buff[strlen(buff)]='\0';
    printf("Resending message to client:%d\n",buff);
    write(c_sock,buff,sizeof(buff));
    usleep(1000);
    
}
int main()
{
    int server,cSockk;
    server=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servAddr,store;
    memset(&server,0,sizeof(server));
    memset(&store,0,sizeof(store));
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(6565);
    servAddr.sin_addr.s_addr=INADDR_ANY;
    socklen_t addrSize;
    if(bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr))<0)
    {
        perror("Error");
        exit(1);
    }
    printf("\nSelective Repeat Server\n");
    listen(server,5);
    addrSize=sizeof(cSockk);
    cSockk=accept(server,(struct sockaddr *)&store,&addrSize);
   time_t t1;
   char msg[50]="Server Message:";
   char buff[50];
   int flag=0;
   fd_set set1;
   struct timeval timeout;
   int rv1,rv2;
   int tot=0;
   int ok[20];
   memset(ok,0,sizeof(ok));
   while(tot<9)
   {
    int toti=tot;
    for(int j=0;j<(3+toti);j++)
    {        
        bzero(buff,sizeof(buff));
        char buff2[60];
        bzero(buff2,sizeof(buff2));
        strcpy(buff2,"Server Message");
        buff2[strlen(buff2)]=(j)+'\0';
        buff2[strlen(buff)]='\0';
        
    }
   } 

    
}