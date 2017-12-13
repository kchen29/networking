#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //server makes WKP
  //and waits for connection
  int ret = mkfifo("WKP", 0600);
  if (ret == -1)
    printf("Failed making wkp: %s\n", strerror(errno));
  else
    printf("Made wkp\n");
  int wkp = open("WKP", O_RDONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  //receive client message
  read(wkp, buf, HANDSHAKE_BUFFER_SIZE);
  printf("read buf: %s\n", buf);
  remove("WKP");

  //write to client
  int fd = open(buf, O_WRONLY);
  write(fd, buf, HANDSHAKE_BUFFER_SIZE);
  printf("write buf: %s\n", buf);
  
  //read from client
  read(wkp, buf, HANDSHAKE_BUFFER_SIZE);
  printf("read buf: %s\n", buf);

  *to_client = fd;
  return wkp;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char pipename[HANDSHAKE_BUFFER_SIZE];
  sprintf(pipename, "%d", getpid());
  int ret = mkfifo(pipename, 0600);
  if (ret == -1)
    printf("Failed makingpipe: %s\n", strerror(errno));
  else
    printf("Made pipe\n");
  int wkp = open("WKP", O_WRONLY);
  //write to server
  write(wkp, pipename, HANDSHAKE_BUFFER_SIZE);
  printf("wrote pipename: %s\n", pipename);
  
  //read from server
  int fd = open(pipename, O_RDONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  read(fd, buf, HANDSHAKE_BUFFER_SIZE);
  printf("read buf: %s\n", buf);
  remove(pipename);
  
  //write to server again
  write(wkp, buf, HANDSHAKE_BUFFER_SIZE);
  printf("wrote buf: %s\n", buf);

  *to_server = wkp;

  return fd;
}
