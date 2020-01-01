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
#include <string.h>
#include <unistd.h>
#include <stdio.h>



#define ClientPort 2224
#define RouterPort 2222

int main(int argc, char *argv[])
{
	char buffer[1024];
	int socket_fd,cc, bin,length;
    struct sockaddr_in serv_ad,dest;
    struct hostent *hostptr;
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
	memset((char *) &serv_ad,0,sizeof(serv_ad));
    memset((char *) &dest,0,sizeof(dest));
  	
	serv_ad.sin_family-(short)AF_INET;
	serv_ad.sin_addr.s_addr=(INADDR_ANY);
	serv_ad.sin_port=ClientPort;


	dest.sin_family-(short)AF_INET;
	dest.sin_addr.s_addr=(INADDR_ANY);
	dest.sin_port=RouterPort;

	cc=bind(socket_fd,(struct sockaddr*) & serv_ad,sizeof(serv_ad));
	
	fflush(stdout);
	
	while(1)
		{
		bzero(buffer,1024);
		fgets(buffer,1024,stdin);

		if(strcmp(buffer,"exit\n")==0)

			{
				strcpy(buffer,"connetion ended \n");
				sendto(socket_fd,&buffer,1024,0,(struct sockaddr *)&dest,sizeof(dest));
				
				close(socket_fd);
				break;
			}

		sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,sizeof(dest));
		bzero(buffer,1024);
		length=sizeof(dest);
		recvfrom(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,&length);
		printf("%s\n",buffer);
		fflush(stdout);
		}
		
		return 0;
}












































// #define RouterPort 2222
// #define CPORT 2224

// int main(int argc, char *argv[])
// {
//   //define variables.
//   int socket_fd;
//   char hello[256]={0};
//   char buffer[256]={0};
//   struct sockaddr_in  router,client; //connector's address information.
//   struct hostent *hostptr; //structure that describe an Internet host.
  

//  //create socket for commuinication
//   socket_fd = socket (AF_INET, SOCK_DGRAM, 0);   // AF_INET= Ipv4, SOCK_DGRAM =UDP Protocol.
//   bzero((char *) &router, sizeof(router)); /* They say you must do this */
  
//   //get the host by the hostname.  
//   hostptr = gethostbyname(argv[1]);
  
//   //define the address used by the socket.
//   router.sin_family = (short) AF_INET;  //get the Ipv4.
//   router.sin_addr.s_addr=htonl(INADDR_ANY);
//   //bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
//   router.sin_port = RouterPort; // get the socket port that i talking with.

//   client.sin_family=(short)AF_INET;
//   client.sin_addr.s_addr=htonl(INADDR_ANY);
//   client.sin_port=CPORT;
// //create the message.

// while(1){
//   scanf("%s",hello); // get the message that the Clinent want to send.
//   //send the message to the socket.
//   sendto(socket_fd,hello,sizeof(hello),0,(struct sockaddr *)&router,sizeof(router));
//   int n =0;
//   int len = sizeof(router);
// // get a message from the server and print it.
//   n=recvfrom(socket_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&router,&len);
//   buffer[n]='\0';
//   printf("Server: %s\n",buffer);
// }
//   return 0;
// }

