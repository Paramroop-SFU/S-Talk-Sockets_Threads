// #ifndef _RECEIVER_H_
// #define _RECEIVER_H_

// //Start background receive thread
// void receiver_init(char* dynMsg);


// void receiver_changeMsg(char *rxMessage);

// //Stop background receive thread and cleanup
// void receiver_close(void);

// #endif
#ifndef _RECEIVER_H_
#define _RECEIVER_H_

// Initialize receiver thread
void receiver_init(int port, const char* localMachine);

// Stop receiver thread and cleanup
void receiver_close(void);

#endif
