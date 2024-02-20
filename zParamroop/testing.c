#include "sendto.h"
#include <stdio.h>
#include "list.h"


int main()
{List*l1 = List_create();
char * hello = (char*)List_trim(l1);
if (hello == NULL)
{
        printf("LLLLLLLLLL\n");
}
        int userport = 0;
        int clientport = 0;
        char hostname[30] = {0};
        printf("s-talk ");
        scanf("%d %s %d",&userport,hostname,&clientport);
        printf(":%d:%s:%d:",userport,hostname,clientport);
        
        receive(userport,l1);
        //char * hello = (char*)List_trim(l1);
        printf("%s",hello);
        
        
}