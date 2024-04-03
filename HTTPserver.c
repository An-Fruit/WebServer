#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#define INPUT_BUFFER_LEN 1024
#define HEADER_AND_RESPONSE_LEN 2048
#define HTTP_PORT 8001
#define MAX_CONNECTIONS 10

int main(int argc, char **argv){

    FILE *html_file = fopen("index.html", "r");     //open the file index.html in read mode
    if(html_file == NULL){
        fprintf(stderr, "FAILED TO OPEN FILE index.html\n");
        return -1;
    }

    char server_response[INPUT_BUFFER_LEN];
    fgets(server_response, INPUT_BUFFER_LEN, html_file);    //put contents of index.html into a buffer

    //status code @ beginning
    char http_header[HEADER_AND_RESPONSE_LEN] = "HTTP/1.1 200 OK\r\n\n";   //return carriage (in case of windows)
    strcat(http_header, server_response);

    //create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //define address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(HTTP_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind socket to address
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //listen for connection(s)
    listen(server_socket, MAX_CONNECTIONS);

    //accept connection(s)
    int client_socket;
    struct sockaddr client_address;
    int client_addr_len = sizeof(client_address);

    while(true){
        //accept client connnection & print out its address
        client_socket = accept(server_socket, &client_address, (socklen_t *) &client_addr_len);
        fprintf(stdout, "CLIENT CONNECTION ACCEPTED\nCLIENT ADDRESS = ");
        for(int i = 0; i < sizeof(client_address.sa_data); i++){
            fprintf(stdout, "%u ", client_address.sa_data[i]);
        }
        fprintf(stdout, "\n");
        
        //send the client the HTTP response
        send(client_socket, http_header, sizeof(http_header), 0);
        
        //close client socket
        close(client_socket);
    }

    close(server_socket);


    
    return 0;
}