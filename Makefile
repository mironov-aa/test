CC=gcc
CFLAGS=-g3 -Wall -Wextra -Wpedantic
SOURCES=main.c list.c

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)
