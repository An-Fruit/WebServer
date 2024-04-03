CC = gcc
CFLAGS = -Wall -Wextra

all: webserverTCP

webserverTCP: server client
	$(CC) $(CFLAGS) -o $@ server.o client.o

server: server.c
	$(CC) $(CFLAGS) -c $< -o server.o

client: client.c
	$(CC) $(CFLAGS) -c $< -o client.o

clean:
	rm -f webserverTCP *.o