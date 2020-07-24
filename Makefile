CC=gcc
CFLAGS=-Wall -Wextra -I. -O1
OBJ=$(patsubst %.h, %.o, $(DEPS))
EXE=$(patsubst %.c, %, $(wildcard *.c))

default:
	$(CC) $(CFLAGS) $@.c -o $@

.PHONY: clean
clean:
	rm -f *.o $(EXE)
