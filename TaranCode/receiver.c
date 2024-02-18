// #include "receiver.h"
// #include <stdio.h>
// #include "general.h"
// #include <pthread.h>
// #include <stdlib.h>
// #include <netdb.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include "list.h"
// #include "receiver.h"


// #define PORT 6001
// #define MSG_MAX_LEN 102
// #define DYNAMIC_LEN 128

// static pthread_t s_threadID;
// static char* s_rxMsg = NULL;

// void* receiveThread(void* unused) {
//     // intililzing the socket
    
//     struct sockaddr_in sin; //local var on stack
//     memset(&sin,0,sizeof(sin));
//     sin.sin_family = AF_INET;
//     sin.sin_addr.s_addr = htonl(INADDR_ANY);
//     //htons ->host to network short
//     sin.sin_port = htons(PORT); //change from hort to htons

//     // create socket PF can be used 
//     int socketDes = socket(AF_INET,SOCK_DGRAM,0);

//     //check errors
//     bind (socketDes, (struct sockaddr*) &sin, sizeof(sin));

//     //check return val

//     while (1)
//     {
//         //Receiving data
//         struct sockaddr_in sinRemote; //Sender's IP address
//         unsigned int sin_len = sizeof(sinRemote);
//         char messageRX[MSG_MAX_LEN];
//         int byteRx = recvfrom(socketDes, messageRX, MSG_MAX_LEN, 0, (struct sockaddr*)&sinRemote,&sin_len);

//         //when string(input) ends
//         int terminateIdx = (byteRx < MSG_MAX_LEN) ? byteRx : MSG_MAX_Len-1;
//         messageRX[terminateIdx] = 0;

//         //gives the port of sender
//         long remotePort = ntohs(sinRemote.sin_port);
        
//         printf("%s (%d bytes): \n\n'%s'\n", s_rxMsg, byteRx, messageRX);
//     }
//     printf("Done rx thread");
//     return NULL;

// }

// void receiver_init(char *dynMsg) {
//     pthread_t threadPID;
    

//     s_rxMsg = dynMsg;

//     pthread_create(&threadPID, //PID(by pointer)
//     NULL, //Attributes
//     receiveThread, //function
//     NULL);   //Arguments

//     // pthread_create(&threadPID2, //PID(by pointer)
//     // NULL, //Attributes
//     // receiveThread, //function
//     // "Ssup");   //Arguments

// }

// void receiver_changeMsg(char* newDynamic) {
    
// }

// void receiver_close(void) {
//     //Cancel thread
//     pthread_cancel(threadPID);


//     //waits for thread to finish
//     pthread_join(threadPID, NULL);
//     // pthread_join(threadPID2, NULL);

// }

#include "receiver.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MSG_MAX_LEN 1024

static pthread_t s_threadID;

void* receiveThread(void* params) {
    int* receiveParams = (int*)params;
    int port = receiveParams[0];
    const char* localMachine = (char*)receiveParams[1];

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);

    int socketDes = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socketDes, (struct sockaddr*) &sin, sizeof(sin));

    while (1) {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRX[MSG_MAX_LEN];
        int byteRx = recvfrom(socketDes, messageRX, MSG_MAX_LEN, 0, (struct sockaddr*)&sinRemote, &sin_len);
        int terminateIdx = (byteRx < MSG_MAX_LEN) ? byteRx : MSG_MAX_LEN - 1;
        messageRX[terminateIdx] = 0;
        printf("Received message: %s\n", messageRX);
    }

    close(socketDes);

    return NULL;
}

void receiver_init(int port, const char* localMachine) {
    int receiveParams[2] = { port, (int)localMachine };
    pthread_create(&s_threadID, NULL, receiveThread, receiveParams);
}

void receiver_close(void) {
    pthread_cancel(s_threadID);
    pthread_join(s_threadID, NULL);
}
