#include <arpa/inet.h>

#include <sys/types.h>

#include <unistd.h>    

#include <strings.h>

#include <netdb.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <signal.h>    

#include <sys/socket.h>

#include <sys/un.h>

#include <netinet/in.h>

#define SIM_LENGTH 10 

#define IP_ADDRESS "?????" 

#define PORT 1337 



int main(int argc, char* argv[])

{ 

  int sock, port,bytesRead; 

  struct sockaddr_in cli_name;

  struct sockaddr_in* saddr;

  struct addrinfo* res;

  char  temp[1024];

  char *fullURL, *hostname,*hostaddr ;

  char buffer[1024];



  printf("Client is alive and establishing socket connection.\n");

  

  if (argc != 2) {  /* error running hostname */

    perror("Usage: hostnamelookup <hostname>\n");

    exit(1);

  }



  fullURL= argv[1]; //get the url from the cmd

  strcpy(temp,fullURL);

  printf("temp URL: %s\n", temp);

  //first take the protocol
  char *protocol =strtok(temp , ":");
  printf(" protocol : %s\n", protocol); 
  if (strstr(temp, ":") != NULL) //if there is more ":" that means that the format is equal to  <protocol>://<hostname>:<port>/<path> */ 
  { 
    hostname = strtok(NULL , ":");
    printf( "hostname : %s\n", hostname);
    port = atoi(strtok(NULL , "/"));
    printf( "port : %d\n", port);
    char *path = strtok(NULL , "/"); 
    printf("path : %s\n", path);
  }
  else // format <protocol>://<hostname>/<path> */
  { 
     hostname = strtok(NULL , "/");
    printf( "hostname : %s\n", hostname);
    port = 80; //if no port assign, the port of web server is 80 by default
    printf( "port : %d\n", port);
    char *path = strtok(NULL , "/");
     printf("path : %s\n", path);
  }

  

  

   

  

  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { // if return other then zero, there is an error

    fprintf(stderr, "Error in resolving hostname %s\n", hostname);

    exit(1);

  }

  

  saddr = (struct sockaddr_in*)res->ai_addr;

  hostaddr = inet_ntoa(saddr->sin_addr); //get hostname IP



  printf("Address for %s is %s\n", hostname, hostaddr);



  

  sock = socket(AF_INET, SOCK_STREAM, 0); //create tcp socket for connection to host

  if (sock < 0)

    { perror ("Error opening channel\n");

      close(sock);

      exit(1);

    }

      

  memset((char *)&cli_name,0, sizeof(cli_name)); 

  

  cli_name.sin_family = AF_INET; 

  cli_name.sin_addr.s_addr = inet_addr(hostaddr);  //changed here IP_ADDRESS to the host address IP

  cli_name.sin_port = htons(port);



   //connect the socket to the ip and port that modified in struct

  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)

    { perror ("Error establishing communications\n");

      close(sock);

      exit(1);

    }

    //sends into buffer, the formatted string

    sprintf(buffer, "GET %s HTTP/1.0\r\nHOST: %s\r\n\r\n", fullURL,hostname);

    //sends the buffer throw the tcp socket

    send(sock, buffer, strlen(buffer), 0);

    do//read data from server

    {

        bzero(buffer, sizeof(buffer)); //reset the buffer

        bytesRead = recv(sock, buffer, sizeof(buffer), 0);

        if ( bytesRead > 0 )

            printf("%s", buffer);

    }

    

    while ( bytesRead > 0 );



  printf("\nExiting now.\n");

  close(sock); 

  exit(0); 



} 