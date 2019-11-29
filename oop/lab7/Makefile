all: oop

oop: Figure.o Triangle.o Rectangle.o Square.o main.o Massive007.o
	g++  Figure.o Triangle.o Rectangle.o Square.o main.o Massive007.o -o oop

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Figure.o: Figure.cpp
	g++ -std=c++11 -c Figure.cpp

Triangle.o: Triangle.cpp
	g++ -std=c++11 -c Triangle.cpp

Rectangle.o: Rectangle.cpp
	g++ -std=c++11 -c Rectangle.cpp

Square.o: Square.cpp
	g++ -std=c++11 -c Square.cpp

Massive007.o: Massive007.cpp
	g++ -std=c++11 -c Massive007.cpp


clean:
	rm -rf *.o hello
