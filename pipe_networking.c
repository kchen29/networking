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
  int fd = open("WKP", O_RDONLY);
  char buf[HANDSHAKE_BUFFER_SIZE];
  read(fd, buf, HANDSHAKE_BUFFER_SIZE);
  close(fd);

  *to_client = atoi(buf);
  return fd;
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
  int fd = open("WKP", O_WRONLY);
  write(fd, pipename, HANDSHAKE_BUFFER_SIZE);
  close(fd);
  *to_server = fd;

  fd = open(pipename, O_RDONLY);
  return fd;
}
