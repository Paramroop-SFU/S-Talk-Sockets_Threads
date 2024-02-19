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

        List* transmission = List_create();

        char* m = "Hello";
        List_prepend(transmission,m);

        receive(userport,transmission);
        printf("The string is: %s\n", (char*)(List_trim(transmission)));
        
        
}