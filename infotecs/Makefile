CC = g++
CFLAGS = -Wall
LDFLAGS = -pthread

.PHONY: all clean

all: server client

server.o: first_app/server.cpp
	$(CC) $(CFLAGS) -c -o first_app/server.o first_app/server.cpp

server: first_app/main.cpp first_app/server.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o first_app/main first_app/main.cpp first_app/server.o

client.o: second_app/client.cpp
	$(CC) $(CFLAGS) -c -o second_app/client.o second_app/client.cpp

client: second_app/main.cpp second_app/client.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o second_app/main second_app/main.cpp second_app/client.o


clean:
	rm -f first_app/*.o first_app/main
	rm -f second_app/*.o second_app/main
