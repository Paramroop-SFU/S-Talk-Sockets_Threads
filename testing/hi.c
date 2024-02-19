#include "list.h"
#include <stdlib.h>
#include <string.h>

int main() {
 

   List* hi = List_create();
     char *buffer = (char*)malloc(100*sizeof(char));
      strcpy(buffer,"Hello");
   List_append(hi,buffer);
    return 0;
}