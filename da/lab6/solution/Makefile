solution: BigInteger.h main.o BigInteger.o
	g++ -std=c++17 -O2 -Wall -pedantic -Werror -Wall -Wno-sign-compare -Wno-long-long -lm -g -o solution BigInteger.o main.o
main.o: BigInteger.h main.cpp
	g++ -std=c++17 -O2 -Wall -pedantic -Werror -Wall -Wno-sign-compare -Wno-long-long -lm -g -c -o main.o main.cpp
BigInteger.o: BigInteger.h BigInteger.cpp
	g++ -std=c++17 -O2 -Wall -pedantic -Werror -Wall -Wno-sign-compare -Wno-long-long -lm -g -c -o BigInteger.o BigInteger.cpp
clean:
	rm -f *.o $(NAME)
