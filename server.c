#include<stdio.h> //input and output operations
#include<string.h>	//get the length of a string@strlen
#include<sys/socket.h> //func and struct for socket ops
#include<arpa/inet.h>	//IP add & netw add func
#include<unistd.h>	//basic file, device,& process ops
#include<time.h> // date and time func
#include<stdbool.h> // the boolean data type 

int main(int argc , char *argv[]){

	int socket_desc , client_sock , c , read_size;//Declare socket variable and size
	struct sockaddr_in server , client; // declare socket structure

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0); //Declare socket descriptor
	if (socket_desc == -1) // catching socket creation error
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;//address family for the socket 
	server.sin_addr.s_addr = INADDR_ANY;//address for incoming request
	server.sin_port = htons( 8080 ); //port designated for binding 
	
	//Bind or assigns a name to a socket.
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen to a port for any incoming request for maximum 3 connection
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	

	if (client_sock < 0) //handling socket error
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
        //while looping and accepts a new connection on a socket and returns a new file descriptor for the connected socket
        while(client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)){
        // Declare message variable
        char buff[80], client_message[] = "From server xyz :";
        //reading the client message in socket decriptor
             read(client_sock, buff, sizeof(buff));
        // concatenates server reply to client message
            strcat(client_message, buff);
	//writes data from a buffer to a file descriptor
           write(client_sock, client_message, strlen(client_message));
           memset(client_message,0, sizeof(client_message));
	}
      return 0;
}


