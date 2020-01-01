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
#define ServerPort 2223
#define RouterPort 2222
#define RAND_MAX 32767

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
	char buffer[1024];
	int socket_fd,bind_fd,recv,fsize;
	struct sockaddr_in serv_ad,from, destA, destC;
	
	socket_fd=socket(AF_INET,SOCK_DGRAM,0);
	memset((char *) &serv_ad,0,sizeof(serv_ad));
	memset((char *) &from,0,sizeof(from));
	memset((char *) &destA,0,sizeof(destA));
	memset((char *) &destC,0,sizeof(destC));

	serv_ad.sin_family=(short)AF_INET;
    serv_ad.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_ad.sin_port=RouterPort;

	destA.sin_family=(short)AF_INET;
    destA.sin_addr.s_addr = htonl(INADDR_ANY);
    destA.sin_port=ClientPort;

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
				
		else
		sendto(socket_fd,buffer,1024,0,(struct sockaddr *)&destA,sizeof(destA));
		
	
	}
return 0;
}





























// #define RouterPort 2222
// #define APORT 2223
// #define CPORT 2224
// #define RAND_MAX 32676
















































// double getRand(){
//      double random_value=0;

//     random_value = (double)rand()/RAND_MAX;
//     return random_value;
// }
// int main(int argc, char *argv[])
// {
//   //define variables.
//   int socket_fd ,fromSize,recv;
//   double check=0;
//   double x = 0;
//   char buffer[256]={0};
//   struct sockaddr_in  router ,ASocket,BSocket ,from; //connector's address information.
//   struct hostent *hostptr; //structure that describe an Internet host.
//   printf("Please enter X:");
//   scanf("%lf",&check);

//  memset((char*)&router,0,sizeof(router));
//  memset((char*)&BSocket,0,sizeof(BSocket));
//  memset((char*)&ASocket,0,sizeof(ASocket));


//  //create socket for commuinication
//   socket_fd = socket (AF_INET, SOCK_DGRAM, 0);   // AF_INET= Ipv4, SOCK_DGRAM =UDP Protocol.
//   bzero((char *) &router, sizeof(router)); /* They say you must do this */
//   bzero((char *) &ASocket, sizeof(ASocket));
//   bzero((char *) &BSocket, sizeof(BSocket));
  
//   //get the host by the hostname.  
//   hostptr = gethostbyname(argv[1]);
  
//   //define the address used by the socket.
//   router.sin_family = (short) AF_INET;  //get the Ipv4.
//   router.sin_addr.s_addr=htonl(INADDR_ANY);
//   router.sin_port = RouterPort; // get the socket port that i talking with.

//   ASocket.sin_family = (short) AF_INET;
//   ASocket.sin_addr.s_addr=htonl(INADDR_ANY);
//   ASocket.sin_port=APORT;

//   BSocket.sin_family=(short)AF_INET;
//   BSocket.sin_addr.s_addr=htonl(INADDR_ANY);
//   BSocket.sin_port=CPORT;



// while (1)
// {
//     fromSize=sizeof(from);
// 	bzero(buffer,256);
// 	recv=recvfrom(socket_fd,buffer,256,0,(struct sockaddr *)&from,&fromSize);
// 	printsin(&from, "recv_udp: ", " Packet from:");
// 	puts(buffer);
// 	fflush(stdout);
// 	if(from.sin_port==CPORT){
//         x=getRand();
//         if(x<check){
//             sendto(socket_fd,buffer,256,0,(struct sockaddr *)&BSocket,sizeof(BSocket));

//         }
//         else{
//             strcpy(buffer,"Message have been lost.");
//             sendto(socket_fd,buffer,256,0,(struct sockaddr *)&ASocket,sizeof(ASocket));
//         }

//     }
//     else
// 		sendto(socket_fd,buffer,256,0,(struct sockaddr *)&BSocket,sizeof(BSocket));

// }
//   return 0;
// }
// void printsin(struct sockaddr_in *sin, char *pname, char* msg){
//    printf("%s\n",pname);
//    printf("%s",msg);
//    char ip[INET_ADDRSTRLEN]; //make char array in the size of the ip adress.
//    inet_ntop(AF_INET,&(sin->sin_addr),ip,INET_ADDRSTRLEN); //use inet_ntop to change the sin_addr to ip that we can print.
//    printf("%s=%s, %s=%d","ip",ip,"port", sin->sin_port);
//   printf("\n"); 
// }
