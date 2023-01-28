#include<stdio.h> //input and output operations
#include<string.h>	//get the length of a string@strlen
#include<sys/socket.h> //func and struct for socket ops
#include<arpa/inet.h>	//IP add & netw add func
#include<unistd.h>	//basic file, device,& process ops

int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	//Declare socket variable and size
	// declare socket structure
	//declare message variable
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");//address for remote server
	server.sin_family = AF_INET;//address family for the socket 
	server.sin_port = htons( 8080 );//port designated for binding 

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error"); //catching socket creation error
		return 1;
	}
	
	puts("Connected\n");
	
	//keep communicating with server
	for(int i = 0; i < 1; i++) {//infinity loop
		//Send some data

                printf("Enter Message: ");
                scanf("%s", message);
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
                printf("%s\n\n",server_reply);
		//if(puts(server_reply)){ break;}
	}
	close(sock);
	return 0;
}
