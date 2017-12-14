#include "pipe_networking.h"
#include <ctype.h>

int main() {
  int to_client;
  int from_client;
  
  
  from_client = server_handshake( &to_client );
  while(1){
    char buf[BUFFER_SIZE];
    //read text from client
    read(from_client, buf, BUFFER_SIZE);
    printf("read buf: %s\n", buf);

    //checks to see if received message
    if(strcmp(buf, "done!") == 0){
      printf("server is done!\n");
      exit(1);
    }


    //change text to uppercase
    int i = 0;
    while (buf[i]) {
      buf[i] = toupper(buf[i]);
      i++;
    }
    printf("modified buf: %s\n", buf);
  
    //write text to client
    int ret;
    ret = write(to_client, buf, BUFFER_SIZE);
    if (ret == -1)
      printf("error writing\n");
    printf("wrote buf: %s\n", buf);

    
  }
}
