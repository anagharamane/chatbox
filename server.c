#include <stdio.h>	// general purpose
#include <stdlib.h> // general purpose
#include <string.h> // general purpose
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for the structures
#include <errno.h>			// for perror
#include <fcntl.h>			// for open
#include <unistd.h>			// for close
#include <arpa/inet.h>
#include <ctype.h> //for toupper function used for converting into upper case


// Main Function
int main(int argc, char *argv[])
{

	
	// accepting port no as an argument
	// checking if port no is passed or not
	if (argc < 2)
	{
		printf("Usage: %s <port_no>\n", argv[0]);
		exit(1);
		return 0;
	}
	// server and client file discriptor and port no

	int sfd, cfd, port_no;
	unsigned int len = sizeof(struct sockaddr_in);		// length of sockaddr_in
	port_no = strtoul(argv[1], NULL, 16);				// Converting string to unsigned long integer

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)		// opening the socket
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in saddr = {0}, caddr = {0};		// structures for server address and client address 
	
	saddr.sin_family = AF_INET; //IPv4

	// The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.

	saddr.sin_port = htons(port_no);
	saddr.sin_addr.s_addr = INADDR_ANY; // Accept any ip address

	//1. Bind is used for binding an address with the socket
	if (bind(sfd, (struct sockaddr *)&saddr, len) < 0)
	{
		perror("bind");
		close(sfd);
		exit(3);
	}

	// listening for connection requests
		if (listen(sfd, 5) < 0)
		{
			perror("listen");
			close(sfd);
			exit(4);
		}
	
	while (1)
	{
		//data to be sent to the clients

		char buf[64]={ 0 };
		char data[64]={ 0 };

			// accepting connections
			if ((cfd = accept(sfd, (struct sockaddr *)&caddr, &len)) < 0)
			{
				perror("accept");
				exit(5);
			}
			

			if (recv(cfd, buf, sizeof(buf), 0) < 0) 
			{
		    perror("recv");
		    exit(5);
			}
			printf("Client says:: %s", buf);

			printf("Server::");
		 	fgets(data,sizeof(data),stdin);
		
			// sending message on connection
			if (send(cfd, data, sizeof(data), 0) < 0)
			{	
				perror("send");
				close(cfd);
				exit(4);
			}
			
			//printing the port no and ip of the client
		
					
			printf("client : %s\tConnected at %d\n", inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
			
		}close(cfd);
				
			
	return 0;
}
