.PHONY: all clean

CC = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -Werror -O0 -g

all: hello

hello.o: hello.c
	$(CC) $(CFLAGS) -c -o $@ $<

hello: hello.o
	$(CC) -o $@ $<

clean:
	rm -f hello.o hello
