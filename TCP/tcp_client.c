#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 


void chat(int sockfd) 
{ 
	char client_message[100];
	char server_message[100];
	
	// Clean buffers:
    	memset(server_message,'\0',sizeof(server_message));
    	memset(client_message,'\0',sizeof(client_message));
	
	int n; 
	
	while(1) { 
		
		//Get message to be sent to server as input
		printf("Enter message to be sent to server: ");
        	scanf("%[^\n]",client_message);
        	getchar();
		
		send(sockfd, client_message, sizeof(client_message), 0);
		 
		recv(sockfd, server_message, sizeof(server_message), 0); 
		printf("Message from Server : %s\n", server_message); 
		if ((strncmp(server_message, "exit", 4)) == 0) { 
			printf("Exiting Client\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	
    	// Create socket:
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	
	if (sockfd == -1) { 
		printf("Socket creation failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created\n"); 
	
	
	struct sockaddr_in server_address; 
	// fill the block of memory with value 0
	memset(&server_address, 0, sizeof(server_address));   


	// Server details :
	// Internet protocol (AF_INET) 
	server_address.sin_family = AF_INET; 
	
	// Address port (16 bits)
	// htons() function translates a short integer from host byte order to network byte order
	server_address.sin_port = htons(PORT); 
	
	// Internet address (32 bits)
	// INADDR_ANY : bind a socket to all IPs of the machine
	server_address.sin_addr.s_addr = INADDR_ANY; 

	// connect the client socket to server socket 
	if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) { 
		printf("Connection to the server failed\n"); 
		exit(0); 
	} 
	else
		printf("Connection to the server established...\n"); 

	// chat between server and client
	chat(sockfd); 

	// close the socket 
	close(sockfd); 
} 
