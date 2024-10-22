
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 


int main() { 

	int socket_fd; 

	// Creating socket
	if ( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("Error while creating socket"); 
		exit(EXIT_FAILURE); 
	} 
	
 	// Server details :
	struct sockaddr_in server_address;
	
	// fill the block of memory with value 0
	memset(&server_address, 0, sizeof(server_address));  
	
	// Internet protocol (AF_INET) 
	server_address.sin_family = AF_INET; 
	
	// Address port (16 bits)
	// htons() function translates a short integer from host byte order to network byte order
	server_address.sin_port = htons(PORT); 
	
	// Internet address (32 bits)
	// INADDR_ANY : bind a socket to all IPs of the machine
	server_address.sin_addr.s_addr = INADDR_ANY; 
	
	char client_message[100];
	char server_message[100];
	
	// Clean buffers:
    	memset(server_message,'\0',sizeof(server_message));
    	memset(client_message,'\0',sizeof(client_message));
	
	
	//Get message to be sent to server as input
	printf("Enter message to be sent to server: ");
        scanf("%[^\n]",client_message);
        getchar();
	
	// Send message to server
	sendto(socket_fd, client_message, strlen(client_message), MSG_CONFIRM, (struct sockaddr *) &server_address, sizeof(server_address));
	printf("Message sent to Server successfully\n"); 
	
	int len;
	
	// Receive the server's response:	
	recvfrom(socket_fd, server_message, sizeof(server_message), MSG_WAITALL, (struct sockaddr *) &server_address, &len); 
        printf("Response from Server : %s\n",server_message);


	close(socket_fd); 
	return 0; 
} 
