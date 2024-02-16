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
    char hello[50] = "hello from client";
    char hellos[50] = "hello from client";
    struct sockaddr_in servaddr = {0};

    int dest = socket(AF_INET,SOCK_DGRAM,0);
    if (dest == -1) return -1;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);
    while (1)
    {
  int message = sendto(dest, (const char*)hello, strlen(hello),0,(const struct sockaddr*)&servaddr, sizeof(servaddr));
    if (message == -1)
    {
        perror("failed to send");
    }
    sleep(12);
    }
  

  
    close(dest);
}