CC = g++
CFLAGS = -std=c++17 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -O3 
FILES = *.cpp
PROG = zzip

all:
	$(CC) $(CFLAGS) -o $(PROG) $(FILES)
clean:
	rm -f *.o $(PROG)

