#include "list.h"
#include <cstdlib>
#include <cstring>

int main() {
 

   List* make = List_create();
     char *buffer = (char*)malloc(100*sizeof(char));
      strcpy(buffer,"Hello");
   // List_append(make,buffer);
    return 0;
}