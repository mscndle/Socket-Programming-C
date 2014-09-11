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


#define MYPORT "3490"
#define BACKLOG 10

int socket(int domain, int type, int protocol);
//int bind(int sockfd, struct sockaddr *myaddr, int addrlen);
//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int gethostname(char *hostname, size_t size);

//STEPS:
//getaddrinfo()	
//socket()	-These 2 steps setup the communication port
//bind()	-Associate the socket above with a port on the machine
//connect()	-If you're a client
//listen()	-If you're a server
//accept()

//Get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main() {
	
	int status;
	int listenStatus;
	int sockfd, new_fd;	//for this host and connecting client host
	struct addrinfo hints, *res;
	char s[INET6_ADDRSTRLEN];
	
	struct sockaddr_storage their_addr;	//to store the client's addr
	socklen_t addr_size;				//client's addr info size

	memset(&hints, 0, sizeof hints);
	hints.ai_family 	= AF_INET;
	hints.ai_socktype 	= SOCK_STREAM;
	hints.ai_flags 		= AI_PASSIVE;

	//Get address of host
	if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	// GETTING HOSTNAME
	size_t size = 8;
	char hostname;
	int hostResult = gethostname(&hostname, size);
	if (hostResult == -1) {
		printf("error on gethostname");
	}
	printf("hostnameResult = %d\n", hostResult);
	printf("hostname = %s\n", &hostname);

	//Create a socket
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("initial server socket descriptor: %d\n", sockfd);

	//Bind the host to the socket (if listening), to the port passed into getaddrinfo
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	//Connect (if client)	
	//--	

	//Listen (if server)
	printf("Listening for incoming connections...\n");
	while (1) {		
		if (listen(sockfd, BACKLOG) == -1) {
			//fprintf(stderr, "%s\n", perror(errno));
			//fprintf(stderr, "%d\n", errno);
			//printf("in if\n");
		} else {
			addr_size = sizeof their_addr;
			new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
			if (new_fd == -1) {
				perror("accept");
				continue;
			}

			inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
			printf("server: got connection from %s\n", s);
			
			// printf("Connection established...\n");
			// printf("New socket descriptor: %d\n", new_fd);

			if (send(new_fd, "Hello, Client!", 14, 0) == -1) {
				perror("send");				
			}			
			close(new_fd);
			exit(0);
		}			
		close(new_fd);
	}

	return 0;
}







