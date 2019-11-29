all: hello

hello: Figure.o Triangle.o Rectangle.o Square.o main.o
	g++  Figure.o Triangle.o Rectangle.o Square.o main.o -o hello

main.o: main.cpp
	g++ -std=c++14 -pthread -c main.cpp

Figure.o: Figure.cpp
	g++ -std=c++14 -c Figure.cpp

Triangle.o: Triangle.cpp
	g++ -std=c++14 -c Triangle.cpp

Rectangle.o: Rectangle.cpp
	g++ -std=c++14 -c Rectangle.cpp

Quadrate.o: Square.cpp
	g++ -std=c++14 -c Square.cpp

clean:
	rm -rf *.o hello
