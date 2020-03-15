CC = gcc
CFLAGS = -Wall -std=c99
SOURCE_FILES = smash.c smash.h commands.c commands.h history.c history.h

all: smash

smash: $(SOURCE_FILES) 
	$(CC) $(CFLAGS) $^ -o $@

debug: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -O0 -g $^ -o smashd

clean:
	rm -f smash smashd
