
#include "sendto.h"

pthread_mutex_t data_control;
pthread_cond_t keyboard_item_ready;
pthread_cond_t received_item_ready;
pthread_t inputW, show, scanM, sendM;
bool end = false;


bool terminate(char *string)
{
  if (string == NULL) // checks if string is NULL
    return false;

  int length = strlen(string); // grabs the length and checks
  if (length == 0)
  {
    return false;
  }
  char first = string[0]; // store first letter
 
  if (first == '!' && length == 1) // check if both conditions are true
    return true;

  return false;
}





void *sendinfo(void *value)
{

  arg_value *val = (arg_value *)value;
  // char hostname[], int clientport, List* sending_data
  char *hostname = val->host;
  int clientport = val->client;
  List *sending_data = val->list_send;
  //char host[30] = hostname;



  // Convert client host name to a IP address
  struct sockaddr_in servaddr= {0};

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  char string_num[30];


  sprintf(string_num, "%d", clientport);
  int hostIP = getaddrinfo(hostname, string_num, &hints, &res);
  if (hostIP != 0)
  {
    perror("getaddrinfo() failed");
    exit(1);
  }

  // create socket
  int dest = socket(AF_INET, SOCK_DGRAM, 0);
  if (dest == -1)
  {
    perror("failed to make socket");
    exit(1);
  }

  // write the server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;
  servaddr.sin_port = htons(clientport);
  freeaddrinfo(res); // Free the linked list


  while (1)
  {
    
    // allowing only one function access the list at a time
    pthread_mutex_lock(&data_control);
    char *hello = (char *)List_trim(sending_data); // get the word from the list
    if (hello == NULL)
    {
      pthread_cond_wait(&keyboard_item_ready, &data_control); // if null make the thread wait for a input
      hello = (char *)List_trim(sending_data);
    }
    pthread_mutex_unlock(&data_control); // give away access to the mutex
    if (hello != NULL)                   // if not null send data
    {
      int message = sendto(dest, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
      if (message == -1)
      {
        perror("failed to send");
        exit(1);
      }
      if (terminate(hello))
      {
        free(hello);    
        pthread_cancel(scanM);
        pthread_cancel(show);
         close(dest);
        return NULL;
      }
      free(hello); // free the data
    }
 
  }

 
  return NULL;
}

void *receive(void *value)
{
  arg_value *val = (arg_value *)value; // get the info from list

  int userport = val->user;
  List *receive_From = val->list_rec; // pull the data

  char hostname[30];
  if (gethostname(hostname, sizeof(hostname)) != 0) // get the users hostname
  {
    perror("failed to get user hostname");
    exit(1);
  }

  char string_num[10];
  sprintf(string_num, "%d", userport); // convert the port number to a string

  // get the ip address from hostname
 
  // create socket
  int dest = socket(AF_INET, SOCK_DGRAM, 0);
  if (dest == -1)
  {
    perror("socket() failed");
    exit(1);
  }

  // fill the information of the socket
  struct sockaddr_in servaddrs = {0};
  servaddrs.sin_family = AF_INET;
  servaddrs.sin_addr.s_addr = INADDR_ANY;
  servaddrs.sin_port = htons(userport);

  // bind the port and socket

  if(bind(dest, (const struct sockaddr *)&servaddrs, sizeof(servaddrs)))
  {
    perror("bind() failed");
    close(dest);
    exit(1);
  }
  socklen_t len = sizeof(servaddrs);
   
  // constantly get the clients data
  while (1)
  {
   
    char buffer[300] = {0}; // buffer for the information
  
    // grab the information from the user
  
    int n = recvfrom(dest, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&servaddrs, &len);
    if (n == -1)
    {
      perror("recvfrom() failed");
      exit(1);
    }
    
    // allocate information for the message
    char *mem_word = (char *)malloc(300 * sizeof(char));
    if (mem_word == NULL)
    {
      perror("failed to allocate memory");
      exit(1);
    }
    strcpy(mem_word, buffer);
    // try to get access of the mutex to access the list
    pthread_mutex_lock(&data_control);
    List_prepend(receive_From, mem_word);
    
    pthread_mutex_unlock(&data_control);
    pthread_cond_signal(&received_item_ready); // signal print to start working again
    
    
  }
  
}

void *keyboard(void *value)
{
  List *sending_data = (List *)value; // list data

  while (1)
  {
    if (end == true)
    {
      return NULL;
    }
    char temp[300]; // word buffer

    scanf("%[^\n]s", temp); // get info
    getchar();
     char *character = (char *)malloc(300 * sizeof(char)); // allocate the data
     strcpy(character,temp);
    pthread_mutex_lock(&data_control); // access the mutex to get access to list
    List_prepend(sending_data, character);
    pthread_mutex_unlock(&data_control);
    pthread_cond_signal(&keyboard_item_ready); // signal sendto if its currently waiting

    if (terminate(character)) // terminate the thread
    {
      return NULL;
    }
  }

  return NULL;
}

void *print_message(void *value) // print messsage
{
  arg_value *val = (arg_value *)value; // get the data from the argument
  List *receive_From = val->list_rec;
  List *sending_data = val->list_send;
  while (1)
  {
    pthread_mutex_lock(&data_control); // try to get into the mutex
    //

    char *print_message = (char *)List_trim(receive_From); // access list and get message
    if (print_message == NULL) // check if message is null
    {
      pthread_cond_wait(&received_item_ready, &data_control); // if so make it wait
      print_message = (char *)List_trim(receive_From); // then try again once it gets the signal
    }
    if (print_message != NULL) // check if message is not null
    {

      if (terminate(print_message)) // if message is !
      {
        printf("Remote Client: %s\n", print_message); // print it then terminate all of the threads
        
         char *character = (char *)malloc(300 * sizeof(char));
         strcpy(character,print_message);
         List_prepend(sending_data, character);
         pthread_cancel(inputW);
         
         pthread_cond_signal(&keyboard_item_ready);
          free(print_message);
        pthread_mutex_unlock(&data_control);
        pthread_exit(NULL);
      }


      printf("Remote Client: %s\n", print_message); // normall just prints
      free(print_message);
      print_message = NULL;
    }
    pthread_mutex_unlock(&data_control); // exit mutex
    
  }
  
}

