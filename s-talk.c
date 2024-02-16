#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include <pthread.h>



int main() {
    int userport = 0;
    int clientport = 0;
    char hostname[30] = {0};

    printf("S-talk ");
    scanf("%d %s %d", &userport, hostname, &clientport);

    printf("%d, %s, %d\n", userport, hostname, clientport);

   
    struct sockaddr_in hostSin = {0};
   struct sockaddr_in clientSin = {0};
    memset(&hostSin,0,sizeof(hostSin));
    memset(&clientSin,0,sizeof(clientSin));

    int destHost = socket(AF_INET,SOCK_DGRAM,0);
    int destClient = socket(AF_INET,SOCK_DGRAM,0);
    if (destHost == -1 || destClient == -1) 
    {
        perror("failed to create socket");
        return -1;
    }

    hostSin.sin_family = AF_INET;
    hostSin.sin_addr = hostname;
    hostSin.sin_port = userport;

    


  

    return 0;
}