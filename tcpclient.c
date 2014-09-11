#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PORT "3490"			//Port that the client will be connecting to
#define MAXDATASIZE 100		//max bytes we can get at once

int socket(int domain, int type, int protocol);
//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main() {

	int sockfd;		//socket descriptor
	int status;	    //for getaddrinfo
	int connStatus;
	int numbytes;
	struct addrinfo hints, *res, *servinfo;					
	char buf[MAXDATASIZE];
	char s[INET6_ADDRSTRLEN];
						
	memset(&hints, 0, sizeof hints);    //sample comment
	hints.ai_family 	= AF_UNSPEC;    //something
	hints.ai_socktype 	= SOCK_STREAM;  //bla
	hints.ai_flags		= AI_PASSIVE;   //bla

	if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
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

	//in case of errors
	if (res == NULL) {
		fprintf(stderr, "client: failed to connect!");
		return 2;
	}

	inet_ntop(res->ai_family, get_in_addr((struct sockaddr *)res->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);

	printf("reached here");

	freeaddrinfo(servinfo);	//not fully sure what this does
	printf("after the freeaddrinfo call");

	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	buf[numbytes] = '\0';
	printf("client: received '%s'\n", buf);
	close(sockfd);
	return 0;

}
