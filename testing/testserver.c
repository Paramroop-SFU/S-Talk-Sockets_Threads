#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include <pthread.h>


int main()
{
    char buffer[50] = {0};
    char buffers[50] = {0};
       struct sockaddr_in servaddr = {0};

    int dest = socket(AF_INET,SOCK_DGRAM,0);
    if (dest == -1) return -1;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    int rc = bind(dest, (const struct sockaddr*)&servaddr,sizeof(servaddr));
    if (rc == -1)
    {
        perror("fail to bind");
        close(dest);
        return -1;
    }
    socklen_t len = 0;
    while (1)
    {


    int n = recvfrom(dest,(char*)buffer,50,MSG_WAITALL,0,&len);

    buffer[n] = '\n';
    printf("%s",buffer);    
    sleep(12);
    }
    close(dest);
    return 0; 
}