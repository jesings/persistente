#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
    puts("Server establishing connection to client");
    *to_client = open("Gandalf",O_RDONLY);
    char* pipename;
    read(*to_client,pipename,HANDSHAKE_BUFFER_SIZE);
    puts("Server recieved private pipe name");
    close(*to_client);
    int upstream = open(pipename,O_WRONLY);
    puts("Connection established");
    char* ack = ACK;
    puts("Acknowledging having recieved the connection");
    write(upstream,ACK,HANDSHAKE_BUFFER_SIZE);
    return upstream;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    char pid[10];
    sprintf(pid,"%d",getpid());
    mkfifo(pid,0644);
    int wrfd = open("Gandalf",O_WRONLY);
    puts("Connection established");
    char* ackbuff = "ipepay";
    puts("Client giving private pipe name to server");
    write(wrfd,ackbuff,HANDSHAKE_BUFFER_SIZE);
    puts("Client establishing a connection with server");
    *to_server =  open("ipepay",O_RDONLY);
    char* ackwait;
    read(*to_server,ackwait,HANDSHAKE_BUFFER_SIZE);
    puts("Acknowledgement recieved");
    return 0;
}
