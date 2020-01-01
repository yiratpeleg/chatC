#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
 

 
int main(int argc, char *argv[])
{
  //define variables.
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  char hello[] = "Hello from server.";
  char buffer[1024]={0};

  struct { char head; u_long  body; char tail;} msg; //struct that represent a message.
 
 //Create socket for communication.
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
 
 //define the address used by the socket.
  s_in.sin_family = (short)AF_INET; // ipv4 or ipv6.
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333); //get the socket port that i talking with.
 
  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  //printsin(&s_in, "UDP-SERVER:", "Local socket is:");
  fflush(stdout);
 
 //binds the unbond sockets to address given.
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 
 //infinity loop,that allways ready to get a maessage
    int len = sizeof(hello);
    fsize = sizeof(from);
    
  for(;;) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,(char*)buffer,1024,0,(struct sockaddr *)&from,&fsize);
    buffer[cc]='\0';
    printf("Client : %s\n",buffer);
    sendto(socket_fd,(const char*)hello,sizeof(hello),0,(struct sockaddr *)&from,fsize);
    fflush(stdout);
  }

  return 0;
}
void printsin(struct sockaddr_in *sin, char *pname, char* msg){
   printf("%s\n",pname);
   printf("%s",msg);
   char ip[INET_ADDRSTRLEN]; //make char array in the size of the ip adress.
   inet_ntop(AF_INET,&(sin->sin_addr),ip,INET_ADDRSTRLEN); //use inet_ntop to change the sin_addr to ip that we can print.
   printf("%s=%s, %s=%d","ip",ip,"port", sin->sin_port);
  printf("\n"); 
}