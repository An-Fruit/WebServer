#include<stdio.h>
#include <stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>      //contains func for converting network addresses
#define PORT 80
#define RESPONSE_SIZE 4096
int main(int argc, char **argv){

    //grab address from args
    char *address = argv[1];

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_aton(address, &server_address.sin_addr.s_addr); //store converted address to correct place

    //connect to server
    connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    char request[] = "GET / HTTP/1.1\r\n\r\n";    //make a get request to root using HTML 1.1
    char response[RESPONSE_SIZE];

    //send the request
    send(client_socket, request, sizeof(request), 0);

    //recieve response
    recv(client_socket, response, sizeof(response), 0);

    //print out response from server
    fprintf(stdout, "SERVER RESPONSE\n---------------------------------------\n%s\n", response);
    
    //close socket
    close(client_socket);
    return 0;   
}