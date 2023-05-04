CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
LDLIBS=-lncurses -lm

all: new_interface

new_interface: new_interface.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

new_interface.o: new_interface.c
	$(CC) $(CFLAGS) -o $@ $<