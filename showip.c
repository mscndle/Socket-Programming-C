#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int getaddrinfo(const char *node,				//hostname or IP
				const char *service,			//"http" or port number		
				const struct addrinfo *hints,	//struct addrinfo already filled out
				struct addrinfo **res);			//linked list of results

int main() {

	int status;
	struct addrinfo hints;		//will be filled up now and contain relevant info
	struct addrinfo *servinfo;	//points to the results eventually
	struct addrinfo *p;			//current pointer in the linked list

	char ipstr[INET6_ADDRSTRLEN];	//Will store the IP address of the host addr we receive				

	memset(&hints, 0, sizeof hints);	//makes sure the struct is empty
	hints.ai_family 	= AF_UNSPEC;
	hints.ai_socktype 	= SOCK_STREAM;
	hints.ai_flags 		= AI_PASSIVE;

	//if getaddrinfo call fails, the programs will exit.
	//If it's a success, *servinfo will point to a linkedlist of struct addrinfo's	
	if ((status = getaddrinfo("www.google.com", "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	int len = 0;	//to compute size of returned *servinfo linked list

	//Traverse through the linkedlist, starting by pointing *p to the head of *servinfo
	for (p = servinfo; p != NULL; p = p->ai_next) {
		
		len++;
		void *addr;
		char *ipver;		

		if (p->ai_family == AF_INET) {	//IPV4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPV4";				
		} else {						//IPV6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);	
			ipver = "IPV6";				
		}

		//convert ip address to string and print it
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf(" %s: %s\n", ipver, ipstr);

	}

	freeaddrinfo(servinfo);

	printf("length of the servinfo linked list: %d\n", len);

	return 0;

}





