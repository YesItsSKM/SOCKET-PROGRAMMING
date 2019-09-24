// TCP-CLIENT

// Baisc C header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of various CONSTANTS, FUNCTIONS and MACROS which will be used in Socket Programming.
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

// Various network or IP CONSTANTS and FUNCTIONS are defined here.
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 4567
#define IP_ADDRESS "127.0.0.1"

#define BUFFER_SIZE 128

typedef struct sockaddr_in Socket;

void main(){

    char buffer[BUFFER_SIZE];

    printf("[ CLIENT - Up and Ready ]\n");

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    Socket server, client;

    socklen_t server_size = sizeof(server);

    memset((Socket *) &server, '\0', server_size);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    server_size = sizeof(server);

    int conn = connect(socketfd, (struct sockaddr *) &server, server_size);

    int n;

    while(1){
    	n = 0;
    	printf("Me : ");
	    
	    while((buffer[n++]=getchar())!='\n');
	    	    buffer[n] = '\0';

		// Send 'exit' command (message).
        if(strncmp(buffer, "exit", 4) == 0){
			int sent_size = send(socketfd, buffer, strlen(buffer), 0);
			break;
		}
	    
        int sent_size = send(socketfd, buffer, strlen(buffer), 0);
	
		bzero(buffer, sizeof(buffer));
		
        int recv_size = recv(socketfd, buffer, BUFFER_SIZE, 0);
		
	    printf("Server : %s", buffer);

		// Connection terminated by the SERVER.
        if(strncmp(buffer, "terminate", 9) == 0)
			break;
	    
		bzero(buffer, sizeof(buffer));
		
		printf("\n");
	}

    printf("\n[ SERVER CLOSED. EXITING. ]\n");

    close(socketfd);
}
