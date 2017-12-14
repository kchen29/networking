#include "pipe_networking.h"
#include <ctype.h>

int main() {
  int to_client;
  int from_client;
  
  while(1){
  
    from_client = server_handshake( &to_client );
    while(1){
      char buf[BUFFER_SIZE];
      //read text from client
      read(from_client, buf, BUFFER_SIZE);
      printf("\n====================\nText received: \n\t%s", buf);
      
      //checks to see if received message
      if(strcmp(buf, "done!") == 0){
	printf("\n\nClient is done!\n");
	printf("\n\n========================================================\nWaiting on new client...\n");
	break;
      }
      
      
      //change text to uppercase
      int i = 0;
      while (buf[i]) {
	buf[i] = toupper(buf[i]);
	i++;
      }
      printf("Changed text to uppercase: \n\t%s", buf);
  
      //write text to client
      int ret;
      ret = write(to_client, buf, BUFFER_SIZE);
      if (ret == -1)
	printf("error writing\n");
      printf("Sent text to client: \n\t%s", buf);
      
      
    }
  }
}
