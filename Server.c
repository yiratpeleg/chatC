#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include  <stdlib.h>


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
  	struct sockaddr_in  serv_add,dest;//destR;

  	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

	memset((char *) &serv_add,0,sizeof(serv_add));
	memset((char *) &dest,0,sizeof(dest));
	//memset((char *) &destR,0,sizeof(destR));

	serv_add.sin_family=(short)AF_INET;
	serv_add.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_add.sin_port=ServerPort;

	dest.sin_family-(short)AF_INET;
	dest.sin_addr.s_addr=(INADDR_ANY);
	dest.sin_port=RouterPort;

	//destR.sin_family=(short)AF_INET;
  //destR.sin_addr.s_addr = htonl(INADDR_ANY);
  //destR.sin_port=PORT_R;

	cc=bind(socket_fd,(struct sockaddr*) & serv_add,sizeof(serv_add));

	//printsin( &serv_add, "RECV_UDP", "Local socket is:");
	fflush(stdout);

	while(1)
	{
	fsize=sizeof(dest);
	bzero(buffer,1024);
	recvfrom(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,&fsize); 
	puts(buffer);
  	bzero(buffer,1024);
	fgets(buffer,1024,stdin);
	if(strcmp(buffer,"exit\n")==0)
		{
			strcpy(buffer,"server closed");
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,sizeof(dest));
			close(socket_fd);
				break;
		}
	sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&dest,sizeof(dest));
	fflush(stdout);
	}	
	return 0;
	}