all: oop

oop: Figure.o Triangle.o Rectangle.o Square.o main.o
	g++ -pthread  Figure.o Triangle.o Rectangle.o Square.o main.o -o oop

main.o: main.cpp
	g++ -O2 -L/usr/include/c++/5 -lfuture -L/usr/include/c++/5 -lfunctional -std=c++14 -c main.cpp

Figure.o: Figure.cpp
	g++ -std=c++14 -c Figure.cpp

Triangle.o: Triangle.cpp
	g++ -std=c++14 -c Triangle.cpp

Rectangle.o: Rectangle.cpp
	g++ -std=c++14 -c Rectangle.cpp

Square.o: Square.cpp
	g++ -std=c++14 -c Square.cpp

clean:
	rm -rf *.o hello
