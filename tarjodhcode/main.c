#include <stdio.h>
#include "general.h"
#include <pthread.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"

#define PORT 6001
#define MSG_MAX_LEN 1024;

static pthread_t s_threadID;
static char* dynMsg = NULL;

void* receiveThread(void* unused) {
    // intililzing the socket
    
    struct sockaddr_in sin; //local var on stack
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    //htons ->host to network short
    sin.sin_port = htons(PORT); //change from hort to htons

    // create socket PF can be used 
    int socketDes = socket(AF_INET,SOCK_DGRAM,0);

    //check errors
    bind (socketDes, (struct sockaddr*) &sin, sizeof(sin));

    //check return val

    while (1)
    {
        //Receiving data
        struct sockaddr_in sinRemote; //Sender's IP address
        unsigned int sin_len = sizeof(sinRemote);
        char messageRX[MSG_MAX_LEN];
        int byteRx = recvfrom(socketDes, messageRX, MSG_MAX_LEN, 0, (struct sockaddr*)&sinRemote,&sin_len);

        //when string(input) ends
        int terminateIdx = (byteRx < MSG_MAX_LEN) ? byteRx : MSG_MAX_Len-1;
        messageRX[terminateIdx] = 0;

        //gives the port of sender
        long remotePort = ntohs(sinRemote.sin_port);
        
        printf("Message received (%d bytes): \n\n'%s'\n", byteRx, messageRX);
    }
    printf("Done rx thread");
    return NULL;

}

int main(int argc, char** args) {



    printf("Message Start\n");
    pthread_t threadPID;

    pthread_create(&threadPID, //PID(by pointer)
    NULL, //Attributes
    receiveThread, //function
    NULL);   //Arguments

    // pthread_create(&threadPID2, //PID(by pointer)
    // NULL, //Attributes
    // receiveThread, //function
    // "Ssup");   //Arguments


    //Wait for user input
    printf("Enter something to finish rx thread\n");
    char x;
    scanf("%c", &x);

    //Cancel thread
    pthread_cancel(threadPID);


    //waits for thread to finish
    pthread_join(threadPID, NULL);
    // pthread_join(threadPID2, NULL);

    printf("Done Message\n");
    
}