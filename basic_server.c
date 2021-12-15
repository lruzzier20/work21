#include "pipe_networking.h"

char* cap(char* s, int size){
  int h;
  for(int i=0;i<size;i++){
    h=s[i];
    if(isalpha(s[i])){
      if(h>96){h=h-32;}else{h=h+32;}
    }
    s[i]=h;
  }
  return s;
}

static void sighandler(int signo){
  if(signo == SIGINT ){
    printf("\nexiting...\n");
    remove(WKP);
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  char s[50];
  int to_client;
  int from_client;
  from_client = server_handshake( &to_client );
  printf("\nready for processing!\n");
  while(1){
    if(read(from_client, s, sizeof(s))<=0){break;}
    write(to_client, cap(s, sizeof(s)), sizeof(s));
  }
  main();
}
