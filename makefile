CC = gcc
CFLAGS = -Wall -Wextra

all: webserverTCP webclientTCP

webclientTCP: client
	$(CC) $(CFLAGS) -o $@ client.o

webserverTCP: server 
	$(CC) $(CFLAGS) -o $@ server.o

server: server.c
	$(CC) $(CFLAGS) -c $< -o server.o

client: client.c
	$(CC) $(CFLAGS) -c $< -o client.o

clean:
	rm -f webserverTCP webclientTCP *.o