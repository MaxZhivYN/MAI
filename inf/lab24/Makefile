CC = gcc
CFLAGS = -lm -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3

lab24:  lexer.o tree.o transform.o main.o
	$(CC) $^ -o $@

clean:
	rm -f *.o lab24
