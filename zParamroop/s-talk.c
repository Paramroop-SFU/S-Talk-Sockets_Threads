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



int main() 
{ 
    //setup for the user info
        int userport = 0;
        int clientport = 0;
        char hostname[30] = {0};
    // Retrieve user hostname
        char user_Hostname[256];
        if (gethostname(user_Hostname, sizeof(user_Hostname)) != 0)
        {
            perror("failed to get user hostname");
            return 1;
        }

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
    
    // Convert user hostname to IP address
        struct addrinfo hints2, *res2;
        memset(&hints2, 0, sizeof(hints2));
        hints2.ai_family = AF_INET; 
        hints2.ai_socktype = SOCK_DGRAM;
        int userIP = getaddrinfo(user_Hostname,NULL,&hints2,&res2);
        if (userIP != 0)
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



    // initialize the user socket to recieve data
        struct sockaddr_in hostSin = {0};
        memset(&hostSin,0,sizeof(hostSin));
        hostSin.sin_family = AF_INET;
        hostSin.sin_addr = ((struct sockaddr_in*)res2->ai_addr)->sin_addr;
        hostSin.sin_port = htons(userport);
        int recieve_fromClient = socket(AF_INET,SOCK_DGRAM,0); 
        if (bind(recieve_fromClient,(struct sockaddr*)&hostSin, sizeof(hostSin)) == -1)
        {
            perror("fail to bind host socket");
            return -1;
        }
    
    // 

}
