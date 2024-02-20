#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

void* print(void* arg)
{
   while(1)
      printf("LOsser\n"); // Added \n for better formatting
   return NULL;
}

void* hi(void* arg)
{
    while(1)
      printf("Winner\n"); // Added \n for better formatting
   return NULL;
}

int main() {
 
   pthread_t s, f;
   pthread_create(&f, NULL, hi, NULL);
   pthread_create(&s, NULL, print, NULL);
   
   pthread_join(f, NULL);  // Added pthread_join to wait for threads to finish
   pthread_join(s, NULL);

   return 0;
}
