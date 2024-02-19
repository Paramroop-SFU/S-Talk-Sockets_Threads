#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


int main()
{
    const char * hello = "hello from client";
    char hellos[50] = "hello from client";
    struct sockaddr_in servaddr = {0};
    const char* hostname = "asb9700u-g02";
  struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int hostIP = getaddrinfo(hostname, "12345", &hints, &res);
    if (hostIP != 0) {
        perror("getaddrinfo() failed");
        return -1;
    }

    int dest = socket(AF_INET,SOCK_DGRAM,0);
    if (dest == -1) return -1;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
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