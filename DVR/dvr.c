#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Link{
    int hop,dest,wt;
};
struct Network{
    int H,L;
    struct Link *link;
};

int main()
{
    int H,L,S,i,j;
    printf("Enter the no of hops\n");
    scanf("%d",&H);
    printf("Enter the no of links\n");
    scanf("%d",&L);
    printf("Enter the source node\n");
    scanf("%d",&S);
    struct Network *n=(struct Network *)malloc(sizeof(struct Network));
    n->H=H;
    n->L=L;
    n->link=(struct Link *)malloc(L * sizeof(struct Link));
    int dist[H];
    for(i=0;i<H;i++)
    dist[i]=INT_MAX;
    dist[S]=0;
    for(i=0;i<L;i++)
    {
        printf("Enter source,destination and weight\n");
        scanf("%d",&n->link[i].hop);
        scanf("%d",&n->link[i].dest);
        scanf("%d",&n->link[i].wt);
    }
     for(i=0;i<H;i++)
     {
        for(j=0;j<L;j++)
        {
            int u=n->link[j].hop;
            int v=n->link[j].dest;
            int wt=n->link[j].wt;
            if(dist[u]!=INT_MAX && dist[u]+wt<dist[v])
            dist[v]=dist[u]+wt;
        }
     }
     
     for(i=0;i<L;i++)
     {
        
        int u=n->link[i].hop;
        int v=n->link[i].dest;
        as a;
        int wt=n->link[i].wt;
        if(dist[u]!=INT_MAX && dist[u]+wt<dist[v])
        printf("Network contains negative weight cycle\n");
     }
     
     printf("\nHop\tDestination from Source");
    for(i=0;i<H;i++)
    printf("\n%d\t%d\n",i,dist[i]);
    free(n->link);
    free(n);
    return 0;
     }