#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include <pthread.h>
#include <sys/types.h>
#include "sendto.h"

pthread_t write, show, scanM, sendM;
List* data_Send;
List* data_Receive;

int main()
{
      data_Send = List_create();
      data_Receive = List_create();
      int userport = 0;
      int clientport = 0;
        char hostname[30] = {0};
        printf("s-talk ");
        scanf("%d %s %d",&userport,hostname,&clientport);
        printf(":%d:%s:%d:",userport,hostname,clientport);
       pthread_create(&scanM, NULL, receive,userport,data_Receive);
       pthread_create(&show,NULL,print_message,data_Receive);
       pthread_create(&write,NULL,keyboard,data_Send);
       pthread_create(&sendM,NULL,sendinfo,hostname,clientport,data_Send);

}




