CC = g++
CFLAGS = -Wall
LDFLAGS = -pthread

.PHONY: all clean

all: server client

client.o: first_app/client.cpp
	$(CC) $(CFLAGS) -c -o first_app/client.o first_app/client.cpp

client: first_app/main.cpp first_app/client.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o first_app/main first_app/main.cpp first_app/client.o

server.o: second_app/server.cpp
	$(CC) $(CFLAGS) -c -o second_app/server.o second_app/server.cpp

server: second_app/main.cpp second_app/server.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o second_app/main second_app/main.cpp second_app/server.o


clean:
	rm -f first_app/*.o first_app/main
	rm -f second_app/*.o second_app/main
