#include<stdio.h>
#include <stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>      //contains func for converting network addresses
#define HTTP_PORT 80
int main(int argc, char **argv){

    //grab address from args
    char *address = argv[1];

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(HTTP_PORT);
    inet_aton(address, &server_address.sin_addr.s_addr); //convert address string to an actual number

    //connect to server
    connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    char request[] = "GET / HTTP/1.1\r\n\r\nFrom: someuser@gmail.com\nUser-Agent: TestHTTPClient/1.0";    //make a get request to root using HTML 1.1
    char response[4096];

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