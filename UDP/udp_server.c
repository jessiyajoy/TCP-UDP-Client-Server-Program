
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 



int main() { 
	int socket_fd;  
	
	// Creating socket
	if ( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	
	struct sockaddr_in server_address, client_address;
 

	// Server details 
	
	// Internet protocol (AF_INET) 
	server_address.sin_family = AF_INET; 
	
	// Address port (16 bits)
	// htons() function translates a short integer from host byte order to network byte order
	server_address.sin_port = htons(PORT); 
	
	// Internet address (32 bits)
	// INADDR_ANY : bind a socket to all IPs of the machine
	server_address.sin_addr.s_addr = INADDR_ANY; 
	
	
	// Bind the socket with the server address 
	if ( bind(socket_fd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 

	len = sizeof(client_address); 
	
	char client_message[100];
	char server_message[100];
	
	// Clean buffers:
    	memset(server_message,'\0',sizeof(server_message));
    	memset(client_message,'\0',sizeof(client_message));
	
	

	n = recvfrom(socket_fd, client_message, strlen(client_message), MSG_WAITALL, ( struct sockaddr *) &client_address, &len); 
	printf("Message from Client : %s\n", client_message);
	
	//Get message to be sent to server as input
	printf("Enter message to be sent to client: ");
        scanf("%[^\n]",server_message);
        getchar();
	
	sendto(socket_fd, server_message, strlen(server_message), MSG_CONFIRM, (const struct sockaddr *) &client_address, len); 
	printf("Message sent to Client successfully.\n"); 
	
	return 0; 
	
} 
