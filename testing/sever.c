#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include <pthread.h>
pthread p1;
//thread_create(p1)

#define PORT 6001
#define MSG_MAX_Len 1024;

int main(int argc, char* argv[])
{
    // intililzing the socket
    
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = hort(PORT);

    // create socket PF can be used 
    int socketDes = socket(AF_INET,SOCK_DGRAM,0);
    bind (socketDes, (struct sockaddr*) &sin, sizeof(sin));

    while (1)
    {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRX[MSG_MAX_Len];
        int byteRx = recvfrom(socketDes, messageRX, MSG_MAX_Len, 0, (struct sockaddr*)&sinRemote,&sin_len);

        int terminateIdx = (byteRx < MSG_MAX_Len) ? byteRx : MSG_MAX_Len-1;
        messageRX[terminateIdx] = 0;
        printf("Message received (%d bytes): \n\n'%s'\n", byteRx, messageRX);

        int incMe = atoi(messageRX);

        char messageTx[MSG_MAX_Len];
        sprintf(messageTx, "Math: %d + 1 = %d\n", incMe, incMe+1);

        sin_len = sizeof(sinRemote);
        sendto (socketDes, messageTx,strlen(messageTx),0,(struct sockaddr *)&sinRemote, sin_len);



    }

}