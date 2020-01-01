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
 

#define ServerPort 2223
#define RouterPort 2222

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
    char *ip = inet_ntoa(sin->sin_addr);
    puts(pname);
    printf("%s ip= %s, port= %d\n", msg, ip, sin->sin_port);
}

  int main(int argc, char *argv[])
{
	char buffer[1024];
	int socket_fd, cc, fsize;
  	struct sockaddr_in  serv_add,dest,destR;

  	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

	memset((char *) &serv_add,0,sizeof(serv_add));
	memset((char *) &dest,0,sizeof(dest));
	memset((char *) &destR,0,sizeof(destR));

	serv_add.sin_family=(short)AF_INET;
	serv_add.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_add.sin_port=ServerPort;

	dest.sin_family-(short)AF_INET;
	dest.sin_addr.s_addr=(INADDR_ANY);
	dest.sin_port=RouterPort;

	destR.sin_family=(short)AF_INET;
    destR.sin_addr.s_addr = htonl(INADDR_ANY);
    destR.sin_port=RouterPort;

	cc=bind(socket_fd,(struct sockaddr*) & serv_add,sizeof(serv_add));

	printsin( &serv_add, "RECV_UDP", "Local socket is:");
	fflush(stdout);
	char buffer2[1024]="got you message";
	while(1)
	{
	
	fsize=sizeof(dest);
	bzero(buffer,1024);
	recvfrom(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,&fsize); 
	puts(buffer);
	sendto(socket_fd,buffer2,1024,0,(struct sockaddr *)&destR,sizeof(destR));
	bzero(buffer,1024);
	fgets(buffer,1024,stdin);

	if(strcmp(buffer,"exit\n")==0)
		{
			strcpy(buffer,"server closed");
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,sizeof(dest));
			fflush(stdout);
		}
	}	
	return 0;
	}










































// #define RouterPort 2222
// #define APORT 2223
 
// int main(int argc, char *argv[])
// {
//   //define variables.
//   int socket_fd, cc, fsize;
//   struct sockaddr_in  s_in,router;
//   char buffer[1024]={0};
//   char message[] = "got the message";

 
//  //Create socket for communication.
//   socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 
//   bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
 
//  //define the address used by the socket.
//   s_in.sin_family = (short)AF_INET; // ipv4 or ipv6.
//   s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
//   s_in.sin_port = APORT; //get the socket port that i talking with.
 

//  router.sin_family=(short)AF_INET;  
//  router.sin_addr.s_addr = htonl(INADDR_ANY);
//  router.sin_port=RouterPort;
 
//  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
//   //printsin(&s_in, "UDP-SERVER:", "Local socket is:");
//   fflush(stdout);
 
//  //binds the unbond sockets to address given.
//   bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 
//  //infinity loop,that allways ready to get a maessage

//   for(;;) {
//     fsize = sizeof(router);
//     cc = recvfrom(socket_fd,(char*)buffer,1024,0,(struct sockaddr *)&router,&fsize);
//     buffer[cc]='\0';
//     printf("Client : %s\n",buffer);
//     sendto(socket_fd,(const char*)message,sizeof(message),0,(struct sockaddr *)&router,fsize);
//     fflush(stdout);
//   }

//   return 0;
// }
