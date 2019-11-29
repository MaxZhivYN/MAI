CC = gcc
CFLAG = -g -std=c99 -w -pipe -03

all: stack_main

stack_main: stack_array.o sort.o stack_main.o
		$(CC) $^ -o $@

clean: rm -f *.o

cleanall: rm -f generate print execute *.o