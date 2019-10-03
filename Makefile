C = gcc
CFLAGS = -g -std=gnu99
THRD = -lpthread


all:
	$(CC) $(CFLAGS) main.c -o server

clean:
	rm server *.o
