CC = gcc
CFLAGS = -Wall -std=c99

all: smash

smash: smash.c smash.h commands.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm smash
