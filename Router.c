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
#include <stdlib.h>

#define ClientPort 2224
#define ServerPort 2223
#define RouterPort 2222

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
    char *ip = inet_ntoa(sin->sin_addr);
    puts(pname);
    printf("%s ip= %s, port= %d\n", msg, ip, sin->sin_port);
}

double Rand()
{
	return(double)rand()/(double)RAND_MAX;
}

int main(int args,char *argv[]){
	double random;
	double x,y;
	printf("enter your choice \n");
	scanf("%lf", &y);
	printf("%f\n",y);
	char buffer[1024];
	int socket_fd,bind_fd,recv,fsize;
	struct sockaddr_in serv_ad,from, destA, destC;
	
	socket_fd=socket(AF_INET,SOCK_DGRAM,0);
	memset((char *) &serv_ad,0,sizeof(serv_ad));
	memset((char *) &from,0,sizeof(from));
	memset((char *) &destA,0,sizeof(destA));
	memset((char *) &destC,0,sizeof(destC));

//router
	serv_ad.sin_family=(short)AF_INET;
    serv_ad.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_ad.sin_port=RouterPort;

//a
	destA.sin_family=(short)AF_INET;
    destA.sin_addr.s_addr = htonl(INADDR_ANY);
    destA.sin_port=ClientPort;
//c
	destC.sin_family=(short)AF_INET;
    destC.sin_addr.s_addr = htonl(INADDR_ANY);
    destC.sin_port=ServerPort;
	
	bind_fd=bind(socket_fd,(struct sockaddr *) &serv_ad,sizeof(serv_ad));


	while(1)
	{

	fsize=sizeof(from);
	bzero(buffer,1024);
	recv=recvfrom(socket_fd,buffer,1024,0,(struct sockaddr *)&from,&fsize);
	printsin(&from, "recv_udp: ", " Packet from:");
	puts(buffer);
	fflush(stdout);
	if(from.sin_port==ClientPort)

		{
			random=Rand();

			if (random>x)
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&destC,sizeof(destC));

			else {
			strcpy(buffer,"messege lost\n");
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&destA,sizeof(destA));
			}
		}
				
	else if(from.sin_port==ServerPort)

		{
			random=Rand();

			if (random>x)
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&destA,sizeof(destA));

			else {
			strcpy(buffer,"messege lost\n");
			sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&destC,sizeof(destC));
			}
		}
	}
return 0;
}