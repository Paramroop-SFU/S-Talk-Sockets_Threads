// #include <stdio.h>
// #include <stdlib.h>
// #include "receiver.h"



// int main(int argc, char** args) {

    

//     printf("Message Start\n");
//     //Start the thread
//     receiver_init("message for you brotha");
    


//     //Wait for user input
//     printf("Enter something to finish rx thread\n");
//     char x;
//     scanf("%c", &x);

//     //thread closing
//     receiver_close();

//     printf("Done Message\n");
//     return 0; 
    
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receiver.h"
#include "sender.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: %s <port> <local_machine> <remote_machine>\n", argv[0]);
        return 1;
    }

    // Extract command-line arguments
    int port = atoi(argv[1]);
    char* localMachine = argv[2];
    char* remoteMachine = argv[3];

    printf("s-talk session initiated with local port: %d, local machine: %s, remote machine: %s\n", port, localMachine, remoteMachine);

    // Initialize sender and receiver threads
    sender_init(port, remoteMachine);
    // receiver_init(port, localMachine);

    // Main loop
    while (1) {
        // Do nothing in main loop, sender and receiver threads handle message sending and receiving
    }

    // Close sender and receiver threads
    sender_close();
    receiver_close();

    printf("s-talk session terminated\n");
    return 0;
}
