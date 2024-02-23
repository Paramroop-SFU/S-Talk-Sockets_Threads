
#include "sendto.h"





int main( int argc,char* argv[])

{

   if (argc < 4)
    {
      perror("failed to give 3 arguments");
      exit(1);
    }
    List *data_Send;

    List *data_Receive;
    data_Send = List_create();

    data_Receive = List_create();
 
    int userport = atoi(argv[1]);
    int clientport = atoi(argv[3]);





    arg_value* UDP_data = (arg_value*)malloc(sizeof(arg_value));
    UDP_data->client = clientport;
    UDP_data->host = argv[2];
    UDP_data->user = userport;
    UDP_data->list_send = data_Send;
    UDP_data->list_rec = data_Receive;
    printf("grabing connection\n");
    pthread_mutex_init(&data_control,NULL);

  //  printf(":%d:%s:%d:", userport, hostname, clientport);

    pthread_create(&scanM, NULL, receive, (void*)UDP_data);

    pthread_create(&show, NULL, print_message, (void*)UDP_data);

    pthread_create(&inputW, NULL, keyboard, (void*)data_Send);

    pthread_create(&sendM, NULL, sendinfo, (void*)UDP_data);

   pthread_join(scanM,NULL);
   pthread_join(show,NULL);
   pthread_join(inputW,NULL);
   pthread_join(sendM,NULL);
   pthread_mutex_destroy(&data_control);
   
   free(UDP_data);
   return 0;
}