#include "sendto.h"

#include "list.h"


int main()
{

  int userport = 0;
        int clientport = 0;
        char hostname[30] = {0};
        printf("s-talk ");
        scanf("%d %s %d",&userport,hostname,&clientport);
        printf(":%d:%s:%d:",userport,hostname,clientport);
        List*l1 = List_create();
        char magic[30] = "hi";
        List_prepend(l1,&magic);
        sendinfo(hostname,clientport,l1);
        
        
}