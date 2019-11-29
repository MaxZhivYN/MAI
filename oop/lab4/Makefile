all: hello

hello: Figure.o Triangle.o Rectangle.o Quadrate.o main.o
	g++  Figure.o Triangle.o Rectangle.o Quadrate.o main.o -o hello

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Figure.o: Figure.cpp
	g++ -std=c++11 -c Figure.cpp

Triangle.o: Triangle.cpp
	g++ -std=c++11 -c Triangle.cpp

Rectangle.o: Rectangle.cpp
	g++ -std=c++11 -c Rectangle.cpp

Quadrate.o: Quadrate.cpp
	g++ -std=c++11 -c Quadrate.cpp

clean:
	rm -rf *.o hello
