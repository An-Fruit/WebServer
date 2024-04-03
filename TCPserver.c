#include <stdio.h>          //writing to output/other stuff
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>     //sockets

#include <netinet/in.h>     //some structs needed from here to store address info

#define PORT 9001
#define MAX_CONNECTIONS 10

int main(int argc, char *argv[]){

    char server_msg[256] = "You have reached the server. Congrats! :)"; //send this text to clients that connect

    //create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);       //address family = internet, socket type = stream, protocol = 0 (TCP)


    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind socket to IP and Port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //listen for connection(s)
    listen(server_socket, MAX_CONNECTIONS); //2nd arg is how many connections can be waiting @ a point in time

    //accept connection(s)
    int client_socket;
    struct sockaddr client_address;
    int client_addr_len = sizeof(client_address);
    client_socket = accept(server_socket, &client_address, (socklen_t *) &client_addr_len);
    fprintf(stdout, "CLIENT CONNECTION ACCEPTED\nCLIENT ADDRESS = ");
    for(int i = 0; i < sizeof(client_address.sa_data); i++){
        fprintf(stdout, "%u ", client_address.sa_data[i]);
    }
    fprintf(stdout, "\n");
    //send info to client socket
    send(client_socket, server_msg, sizeof(server_msg), 0);

    //close socket
    close(server_socket);

    
    return 0;
}