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
		
		recv(sockfd, client_message, sizeof( client_message), 0); 
		printf("Message from Client : %s\n", client_message); 
		
		//Get message to be sent to client as input
		printf("Enter message to be sent to Client: ");
        	scanf("%[^\n]", server_message);
        	getchar();
		
		send(sockfd, server_message, sizeof( server_message), 0);
		 
		if ((strncmp( server_message, "exit", 4)) == 0) { 
			printf("Exiting Server\n"); 
			break; 
		} 
	} 
} 



int main() 
{ 
	int sockfd, connection_socket_fd, len; 

    	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Socket creation failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket created successfully\n"); 
		
	
	struct sockaddr_in server_address, client_address; 
	// fill the block of memory with value 0
	memset(&server_address, 0, sizeof(server_address)); 

	//Server details :
	// Internet protocol (AF_INET) 
	server_address.sin_family = AF_INET; 
	
	// Address port (16 bits)
	// htons() function translates a short integer from host byte order to network byte order
	server_address.sin_port = htons(PORT); 
	
	// Internet address (32 bits)
	// INADDR_ANY : bind a socket to all IPs of the machine
	server_address.sin_addr.s_addr = INADDR_ANY; 
	

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address))) != 0) { 
		printf("Socket bind failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listening failed\n"); 
		exit(0); 
	} 
	else
		printf("Server listening...\n");
		 
	len = sizeof(client_address); 

	// Accept the data packet from client and verification 
	connection_socket_fd = accept(sockfd, (struct sockaddr *)&client_address, &len); 
	if (connection_socket_fd < 0) { 
		printf("Server failed to acccept connection\n"); 
		exit(0); 
	} 
	else
		printf("Server acccepted connection from Client...\n"); 

	// chat between server and client
	chat(connection_socket_fd); 

	// After chatting close the socket 
	close(sockfd); 
} 
