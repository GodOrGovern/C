CC = gcc
CFLAGS = -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O3 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow
LDFLAGS = -lm

PROJ = vector
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

vector: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(PROJ)
