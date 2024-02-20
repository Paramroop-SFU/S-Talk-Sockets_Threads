
#include "sendto.h"





void sendinfo(char hostname[], int clientport, List* sending_data)
{    
    struct sockaddr_in servaddr = {0};
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    char string_num[10];
    sprintf(string_num,"%d",clientport);
    int hostIP = getaddrinfo(hostname, string_num, &hints, &res);
    if (hostIP != 0) {
        perror("getaddrinfo() failed");
        exit(1);
    }

    int dest = socket(AF_INET,SOCK_DGRAM,0);
    if (dest == -1)
    {
      perror("failed to make socket");
      exit(1);
    }

      servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr.s_addr;
    servaddr.sin_port = htons(clientport);

    char * hello = (char*)List_trim(sending_data);

while(1)
{
  if (hello != NULL)
  {
    
    int message = sendto(dest, (const char*)hello, strlen(hello),0,(const struct sockaddr*)&servaddr, sizeof(servaddr));
    if (message == -1)
    {
        perror("failed to send");
        exit(1);
    }
  }
  else
  {

  }
}
    
    close(dest);

}


void receive(int userport,List* receive_From)
{
    char buffer[100] = {0};
    char hostname[15];
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        perror("failed to get user hostname");
        exit(1);
    }
    char string_num[10];
    sprintf(string_num,"%d",userport);
    
    struct addrinfo hintss, *ress;
    memset(&hintss, 0, sizeof(hintss));
    hintss.ai_family = AF_INET;
    hintss.ai_socktype = SOCK_DGRAM;

    int hostIP = getaddrinfo(hostname, string_num, &hintss, &ress);
    if (hostIP != 0) {
        perror("getaddrinfo() failed");
        exit(1);
    }
  

    int dest = socket(AF_INET, SOCK_DGRAM, 0);
    if (dest == -1) {
        perror("socket() failed");
        exit(1);
    }
    struct sockaddr_in servaddrs = {0};
    servaddrs.sin_family = AF_INET;
    servaddrs.sin_addr.s_addr = ((struct sockaddr_in*)ress->ai_addr)->sin_addr.s_addr;
    servaddrs.sin_port = htons(userport);
      int rc = bind(dest, (const struct sockaddr*)&servaddrs, sizeof(servaddrs));
    if (rc == -1) {
        perror("bind() failed");
        close(dest);
        exit(1);
    }
  socklen_t len = sizeof(servaddrs);

        int n = recvfrom(dest, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&servaddrs, &len);
        if (n == -1) {
            perror("recvfrom() failed");
            
        }


        printf("%s\n", buffer);
        // if i want to make it better make malloc depend on string size
      char* mem_word = (char*)malloc(100*sizeof(char));
      if (mem_word == NULL)
      {
        perror("failed to allocate memory");
        exit(1);
      }
    strcpy(mem_word,buffer);
    List_prepend(receive_From,mem_word);
     freeaddrinfo(ress);  // Free the linked list
     close(dest);
   // return 0;
}


void keyboard(List* sending_data)
{
  while(1)
  {
    char *character = (char*)malloc(100*sizeof(char));
    scanf("%s",character);
    List_prepend(sending_data,character); 
  }
}

void print_message(List*receive_From)
{
  while(1)
  {
    char* print_message = (char*)List_trim(receive_From);
    if (print_message != NULL)
    {
      printf("%s\n",print_message);
    }
  }
}
