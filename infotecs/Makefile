CC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread

.PHONY: all clean

all: monitor signal

monitor: monitor.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

signal: signal.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f monitor
	rm -f signal
