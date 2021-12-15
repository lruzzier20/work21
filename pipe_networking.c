#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  char ret[10];
  mkfifo(WKP, 0644);
  printf("\nmade WKP, now waiting\n");
  from_client=open(WKP, O_RDONLY);
  printf("connected to client with WKP\n");
  char spipe[20];
  read(from_client, spipe, sizeof(spipe));
  printf("read secret pipe name from WKP\n");
  remove(WKP);
  *to_client=open(spipe, O_WRONLY);
  printf("connected to client through secret pipe\n");
  write(*to_client, ACK, 10);
  printf("sent acknowledgement to client\n");
  read(from_client, ret, 10);
  if(strcmp(ret, ACK)){printf("Oops! Acknowledgement not successfully returned!");}
  printf("acknowledgement successfully returned, connection complete!");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;
  char buffer[20];
  char ack[20];
  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0644);
  *to_server=open(WKP, O_WRONLY);
  printf("connected to server with WKP\n");
  write(*to_server, buffer, sizeof(buffer));
  printf("sent secret pipe name to server through WKP\n");
  from_server=open(buffer, O_RDONLY);
  printf("connected to server through secret pipe\n");
  read(from_server, ack, 10);
  printf("received acknowledgement from server\n");
  remove(buffer);
  write(*to_server, ack, 10);
  printf("returned acknowledgement to server, connection complete!");
  return from_server;
}
