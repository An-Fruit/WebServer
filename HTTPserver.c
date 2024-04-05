#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#define RESPONSE_LEN 2048
#define HTTP_PORT 80
#define MAX_CONNECTIONS 10

/**
 * @param fp a file pointer to the file we want to get the size of
 * @return the size of the file in bytes
*/
size_t file_size(FILE *fp){
    int prev_loc = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, prev_loc, SEEK_SET);
    return size;
}

/**
 * initializes server address
 * @param server_address the address we want to init
 * @param port the port number that we want to 
*/

void init_server_address(struct sockaddr_in *server_address, unsigned short port){
        //define address
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port);
    server_address->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char **argv){

    FILE *html_file = fopen("index.html", "r");     //open the file index.html in read mode
    if(html_file == NULL){
        fprintf(stderr, "FAILED TO OPEN FILE index.html\n");
        return -1;
    }

    //put the server response in a buffer
    char server_response[RESPONSE_LEN] = "HTTP/1.1 200 OK\r\n\nServer: MyWebServer/1.0\nDate: "; 
    char message_body[4096];
    fgets(message_body, 4096, html_file);
    strcat(server_response, message_body);

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
        send(client_socket, server_response, sizeof(server_response), 0);
        
        //close client socket
        close(client_socket);
    }

    close(server_socket);


    
    return 0;
}