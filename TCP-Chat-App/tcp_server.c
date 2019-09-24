// TCP-SERVER

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

    printf("[ SERVER - Up and Ready ]\n");

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    Socket server, client;

    socklen_t server_size = sizeof(server);
    socklen_t client_size = sizeof(client);

    memset((Socket *) &server, '\0', server_size);
    memset((Socket *) &server, '\0', client_size);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    server_size = sizeof(server);

    int bind_id = bind(socketfd, (struct sockaddr *)&server, sizeof(server));

    int listen_id = listen(socketfd, 1);

    int clientfd = accept(socketfd, (struct sockaddr *) &client, &client_size);

    printf("\n[ CLIENT CONNECTED ] \n\n");

    int n;

    while(1){
		n = 0;
        
        int recv_size = recv(clientfd, buffer, BUFFER_SIZE, 0);
	    printf("Client : %s", buffer);

		// Connection terminated by CLIENT.
        if(strncmp(buffer, "exit", 4) == 0)
			break;
			
		bzero(buffer, sizeof(buffer));		
	
		printf("SERVER : ");
	    
	    while((buffer[n++] = getchar()) != '\n');
	    buffer[n] = '\0';

		// Send connection termination command(message).
        if(strncmp(buffer, "terminate", 9) == 0){
			int sent_size = send(clientfd, buffer, strlen(buffer), 0);
			break;
		}
	    
        int sent_size = send(clientfd, buffer, strlen(buffer), 0);
	    
		bzero(buffer, sizeof(buffer));
		
		printf("\n");
	}

    printf("\n[ CLIENT LEFT, SERVER CLOSED. ]\n");

    close(clientfd);
    close(socketfd);
}
