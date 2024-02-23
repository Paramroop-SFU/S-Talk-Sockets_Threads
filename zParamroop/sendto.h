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

extern pthread_mutex_t data_control;
extern pthread_cond_t keyboard_item_ready;
extern pthread_cond_t received_item_ready;
extern pthread_t inputW, show, scanM, sendM;

struct arg_value
{
    int user;
    int client;
    char*host;
    List* list_send;
    List* list_rec;
};

typedef struct arg_value arg_value;


// the function of sending data
void* sendinfo(void* value);

void* receive(void *value);

void* keyboard(void* value);

void* print_message(void*value);

bool terminate(char*string);

void free2(void* pitem);

//12345 codespaces-4a1507 12345

// *** VSCODE GITHUB *****
//12345 codespaces-4a1507 12346
//12346 codespaces-4a1507 12345

 //***** For CSIL ********
// ./s-talk 12345 asb9700u-g02 12346
// ./s-talk 12346 asb9700u-g02 12345


