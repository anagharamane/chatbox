//take input from client ,press enter text goes to server, server converts into upper case and gives back to client-do the same using while loop

#include <stdio.h>  // general purpose
#include <stdlib.h> // general purpose
#include <string.h> // general purpose
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for the structures
#include <errno.h>      // for perror
#include <fcntl.h>      // for open
#include <unistd.h>     // for close
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	
	
    if (argc < 3)
    { // using command line argument
        printf("Usage: %s <serv_ip> <serv_port>\n", argv[0]);
        exit(1);
    }
    unsigned int len = sizeof(struct sockaddr_in);
    int cfd, serv_port;
  
	
	
    serv_port = strtoul(argv[2], NULL, 16); //string to unsigned long atoi can also be used

   
    struct sockaddr_in saddr = {0};
    saddr.sin_family = AF_INET;                 // set to AF_INET
    saddr.sin_port = htons(serv_port);          // Port number
    saddr.sin_addr.s_addr = inet_addr(argv[1]); // IP address eg "192.168.1.1"

	while(1)
	{
  		char data[64] = { 0 };
	 	char buf[64] = { 0 };
 		if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   		 {
        	perror("socket");
        	exit(2);
   		 }

    	if (connect(cfd, (struct sockaddr *) &saddr, len) < 0) {
			perror("connect");
			close(cfd);
			exit(3);
   		 }

	
		 printf("Client::");
		 fgets(data,sizeof(data),stdin);
	
		 if (send(cfd, data, strlen(data), 0) < 0)
		 {
				perror("send");
				close(cfd);
				exit(4);
		 }
	
	
		if (recv(cfd, buf, sizeof(buf), 0) < 0)
		 {
		    perror("recv");
		    exit(5);
		 }

		printf("Server says:: %s", buf);
		
	}	close(cfd);

	
    return 0;
}
