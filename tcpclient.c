#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#define SERVER_PORT "3490"

int socket(int domain, int type, int protocol);
//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);


int main() {

	int sockfd;		//socket descriptor
	int status;	    //for getaddrinfo
	int connStatus;
	struct addrinfo hints, *res;					
						
	memset(&hints, 0, sizeof hints);    //sample comment
	hints.ai_family 	= AF_UNSPEC;    //something
	hints.ai_socktype 	= SOCK_STREAM;  //bla
	hints.ai_flags		= AI_PASSIVE;   //bla

	if ((status = getaddrinfo(NULL, SERVER_PORT, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo error %s\n", gai_strerror(status));
		exit(1);
	}

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("client socket descriptor: %d\n", sockfd);

	//bind(sockfd, res->ai_addr, res->ai_addrlen);
	//clients don't need to bind

	printf("Attempting to connect now...\n");
	if ((connStatus = connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1) {
		fprintf(stderr, "Error on connecting: %d\n", errno);
	} else {
		printf("yay. connected!\n");
	}
	


}
