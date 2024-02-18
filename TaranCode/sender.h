// #ifndef _SENDER_H_
// #define _SENDER_H_

// void sender_init(char* dynMsg);
// // void sender_sendMsg(const char* message);
// void sender_close(void);

// #endif

#ifndef _SENDER_H_
#define _SENDER_H_

// Initialize sender thread
void sender_init(int port, const char* remoteMachine);

// Stop sender thread and cleanup
void sender_close(void);

#endif

