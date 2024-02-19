
#include "receive.h"
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

void receive(int userport,List* receive_From)
{

    // Retrieve user hostname
    char user_Hostname[256];
    if (gethostname(user_Hostname, sizeof(user_Hostname)) != 0)
    {
        perror("failed to get user hostname");
        exit(1);
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
            exit(1);
        }

    // initialize the user socket to recieve data
    struct sockaddr_in hostSin = {0};

    hostSin.sin_family = AF_INET;
    //hostSin.sin_addr = ((struct sockaddr_in*)res2->ai_addr)->sin_addr;
    hostSin.sin_addr.s_addr = htonl(INADDR_ANY);
    hostSin.sin_port = htons(12345);
    int recieve_fromClient = socket(AF_INET,SOCK_DGRAM,0); 
    if (bind(recieve_fromClient,(struct sockaddr*)&hostSin, sizeof(hostSin)) == -1)
    {
        perror("fail to bind host socket");
        exit(1);
    }

    socklen_t len = sizeof(hostSin);

    char *buffer = (char*)malloc(100*sizeof(char));
    int n = recvfrom(recieve_fromClient, buffer,(sizeof(buffer))-1,0, (struct sockaddr*)&hostSin, &len);
    if ( n == -1)
    {
        perror("failed to receive data");
        exit(-1);
    }
    
    List_prepend(receive_From,buffer);





}
