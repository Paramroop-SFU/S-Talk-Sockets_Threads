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



pthread_t sending;

void send(char* hostname, int clientport)
{
   
    // convert client hostname to IP address
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET; 
        hints.ai_socktype = SOCK_DGRAM;
        int clentIP = getaddrinfo(hostname,NULL,&hints,&res);
        if (clentIP != 0)
        {
            perror("getaddrinfo() failed");
            return -1;
        }
    

     // initizling the client socket to send data
        struct sockaddr_in clientSin = {0};
        memset(&clientSin,0,sizeof(clientSin));
        clientSin.sin_family = AF_INET;
        clientSin.sin_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
        clientSin.sin_port = htons(clientport);

    // making the socket to send the data
      int sendtoClient = socket(AF_INET,SOCK_DGRAM,0);
      if (bind(sendtoClient,(struct sockaddr*)&clientSin, sizeof(clientSin)) == -1)
        {
            perror("fail to bind host socket");
            return -1;
        }

    
    

}




void *send message(NULL)
{

}