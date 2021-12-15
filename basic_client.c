#include "pipe_networking.h"


int main() {
  char s[50];
  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );
  while(1){
    printf("\nEnter a string: ");
    fgets(s, 50, stdin);
    if(strcmp(s,"exit")==0){printf("now closing!"); write(to_server, "now closing", 20); break;}
    write(to_server, s, sizeof(s));
    read(from_server, s, sizeof(s));
    printf("\nReturned string: %s", s);
  }
}
