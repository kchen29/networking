#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  char buf[BUFFER_SIZE];
  //get text from stdin
  printf("Input text:\n");
  fgets(buf, BUFFER_SIZE, stdin);

  //write text to server
  write(to_server, buf, BUFFER_SIZE);
  printf("wrote buf: %s\n", buf);

  //read text from server
  int ret;
  ret = read(from_server, buf, BUFFER_SIZE);
  printf("ret: %d\n", ret);
  
  printf("read buf: %s\n", buf);
}
