#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#define MYPORT "3490"
#define BACKLOG 10

int socket(int domain, int type, int protocol);
//int bind(int sockfd, struct sockaddr *myaddr, int addrlen);
//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

//STEPS:
//getaddrinfo()	
//socket()	-These 2 steps setup the communication port
//bind()	-Associate the socket above with a port on the machine
//connect()	-If you're a client
//listen()	-If you're a server
//accept()



int main() {
	
	int status;
	int listenStatus;
	int sockfd, new_fd;	//for this host and connecting client host
	struct addrinfo hints, *res;
	
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

// 	 // loop through all the results and bind to the first we can
//     for(p = servinfo; p != NULL; p = p->ai_next) {
//         if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
//             perror("server: socket");
// 			continue; 
// 		}

//         if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
//                 sizeof(int)) == -1) {
//             perror("setsockopt");
// exit(1); }
//         if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
//             close(sockfd);
//             perror("server: bind");
// continue; }
// break; }

	//Create a socket
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("initial server socket descriptor: %d\n", sockfd);

	//Bind the host to the socket (if listening), to the port passed into getaddrinfo
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	//Connect (if client)	


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
			
			printf("connection established\n");
			printf("new socket descriptor: %d\n", new_fd);

			int clientAddr = (((struct sockaddr_in *)&their_addr)->sin_addr.s_addr);

			printf("client's address: %d\n", clientAddr);
		}			
	}
	

	//send() and recv() - TCP (OR)



	//sendto() and recvfrom() - UDP





}