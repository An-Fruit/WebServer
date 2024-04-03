#include <stdio.h>          //writing to output/other stuff
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>     //sockets

#include <netinet/in.h>     //some structs needed from here to store address info

#define PORT 9001           

int main(int argc, char *argv[]){

    //create socket
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);       //address family = internet, socket type = stream, protocol = 0 (TCP)

    //specify socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;            //set server address family
    server_address.sin_port = htons(PORT);          //set server port
    server_address.sin_addr.s_addr = INADDR_ANY;    //set server address

    int connect_stat = connect(socket_descriptor, (struct sockaddr *) &server_address, sizeof(server_address));        //connect to the server socket
    if(connect_stat == -1){
        fprintf(stderr, "CONNECTION TO ADDRESS FAILED\nPORT = %d\nSERVER ADDRESS = %d\n", PORT, INADDR_ANY);
    }
    

    return 0;
}