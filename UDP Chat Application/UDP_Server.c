#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 128

typedef struct sockaddr_in Socket;

void main(){
    int port_number = 4444;
    int n = 0;
    const char *server_ip = "127.0.0.1";
    char buffer[BUFFER_SIZE], conn[20];
    
    Socket serverAddr, clientAddr;
    socklen_t clientAddr_size;

    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset((Socket *)&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_number);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);

    bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    clientAddr_size = sizeof(clientAddr);

    const char *client_ip = inet_ntoa(clientAddr.sin_addr);
    
    printf("[SERVER UP & READY]\n");

	while(1){
		n = 0;
		recvfrom(socketfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &clientAddr_size);
	    printf("Client : %s", buffer);

		if(strncmp(buffer, "exit", 4) == 0)
			break;
			
		bzero(buffer, sizeof(buffer));		
	
		printf("SERVER : ");
	    
	    while((buffer[n++] = getchar()) != '\n');
	    buffer[n] = '\0';
	    
	    sendto(socketfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, clientAddr_size);
	    
		bzero(buffer, sizeof(buffer));
		
		printf("\n");
	}
	
	printf("\n[CLIENT LEFT, SERVER CLOSED.]\n");
	
	close(socketfd);
}
