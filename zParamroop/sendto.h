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




// the function of sending data
void sendinfo(char hostname[], int clientport,List* sending_data);

void receive(int userport,List* receive_From);

void keyboard(List*sending_data);

void print_message(List*receive_From);






