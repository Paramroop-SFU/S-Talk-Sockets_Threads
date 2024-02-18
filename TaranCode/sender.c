#include "sender.h"
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

void* sendThread(void* params) {
    int* sendParams = (int*)params;
    int port = sendParams[0];
    const char* remoteMachine = (char*)sendParams[1];

    struct sockaddr_in sin;
    struct hostent *host = gethostbyname(remoteMachine);
    if (host == NULL) {
        printf("Error: Cannot resolve remote machine %s\n", remoteMachine);
        return NULL;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    memcpy(&sin.sin_addr, host->h_addr_list[0], host->h_length);

    int socketDes = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDes < 0) {
        printf("Error: Failed to create socket\n");
        return NULL;
    }

    char messageToSend[MSG_MAX_LEN];
    while (1) {
        printf("Enter message to send: ");
        fgets(messageToSend, sizeof(messageToSend), stdin);
        sendto(socketDes, messageToSend, strlen(messageToSend), 0, (struct sockaddr*)&sin, sizeof(sin));
    }

    close(socketDes);

    return NULL;
}

void sender_init(int port, const char* remoteMachine) {
    int sendParams[2] = { port, (int)remoteMachine };
    pthread_create(&s_threadID, NULL, sendThread, sendParams);
}

void sender_close(void) {
    pthread_cancel(s_threadID);
    pthread_join(s_threadID, NULL);
}
