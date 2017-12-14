#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  
  from_server = client_handshake( &to_server );
  
  while(1){
    char buf[BUFFER_SIZE];
    //get text from stdin
    printf("Input text:\n");
    fgets(buf, BUFFER_SIZE, stdin);

    //checks to see if buf is q
    if(strcmp(buf, "q\n") == 0){
      write(to_server, "done!", BUFFER_SIZE);
      printf("client is done!\n");
      exit(1);
    }



    //write text to server
    write(to_server, buf, BUFFER_SIZE);
    printf("wrote buf: %s\n", buf);

    //read text from server
    int ret;
    ret = read(from_server, buf, BUFFER_SIZE);
    printf("ret: %d\n", ret);
  
    printf("read buf: %s\n", buf);
  

  }

}
