#include <stdio.h>          //writing to output/other stuff
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>     //sockets

#include <netinet/in.h>     //some structs needed from here to store address info

int main(int argc, char *argv[]){

    //create socket
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);       //address family = internet, socket type = stream, protocol = 0 (TCP)

    
    return 0;
}