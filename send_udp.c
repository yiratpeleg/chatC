#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  //define variables.
  int socket_fd;
  char hello[]="Hello from orian and yirat.";
  char buffer[256]={0};
  struct sockaddr_in  dest; //connector's address information.
  struct hostent *hostptr; //structure that describe an Internet host.
  
 //create socket for commuinication
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);   // AF_INET= Ipv4, SOCK_DGRAM =UDP Protocol.
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */
  
  //get the host by the hostname.  
  hostptr = gethostbyname(argv[1]);
  
  //define the address used by the socket.
  dest.sin_family = (short) AF_INET;  //get the Ipv4.
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333); // get the socket port that i talking with.

//send the message to the socket.
  sendto(socket_fd,hello,sizeof(hello),0,(struct sockaddr *)&dest,sizeof(dest));

  int n =0;
  int len = sizeof(dest);
// get a message from the server and print it.
  n=recvfrom(socket_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&dest,&len);
  buffer[n]='\0';
  printf("Server: %s\n",buffer);
  return 0;
}

