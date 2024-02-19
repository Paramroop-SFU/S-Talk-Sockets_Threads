#include "sendto.h"
#include "receive.h"
#include "list.h"


int main()
{
        int userport = 0;
        int clientport = 0;
        char hostname[30] = {0};
        printf("s-talk ");
        scanf("%d %s %d",&userport,hostname,&clientport);
        List* broadcast = List_create();

        char* m = "Hello";
        List_prepend(broadcast,m);
        sendinfo(hostname,clientport,broadcast);
        return 0;
       

        
        
}