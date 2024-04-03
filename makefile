CC = gcc
CFLAGS = -Wall -Wextra

all: TCP HTTP

TCP: TCPserver TCPclient

TCPserver: TCPserver.c
	$(CC) $(CFLAGS) -c $< -o TCPserver.o
	$(CC) $(CFLAGS) -o $@ TCPserver.o

TCPclient: TCPclient.c
	$(CC) $(CFLAGS) -c $< -o TCPclient.o
	$(CC) $(CFLAGS) -o $@ TCPclient.o

HTTP: HTTPserver HTTPclient

HTTPserver: HTTPserver.c
	$(CC) $(CFLAGS) -c $< -o HTTPserver.o
	$(CC) $(CFLAGS) -o $@ HTTPserver.o

HTTPclient: HTTPclient.c
	$(CC) $(CFLAGS) -c $< -o HTTPclient.o
	$(CC) $(CFLAGS) -o $@ HTTPclient.o

clean:
	rm -f TCPserver TCPclient HTTPserver HTTPclient *.o