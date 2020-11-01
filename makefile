program: checker.o generator.o ioaddr.o main.o wrapper.hpp
	g++ -g checker.o generator.o ioaddr.o main.o -o program

checker: checker.hpp checker.cpp
	g++ -g checker.cpp -c -o checker.o

generator: generator.hpp generator.cpp
	g++ -g generator.cpp -c -o generator.o

ioaddr: ioaddr.cpp ioaddr.hpp
	g++ -g ioaddr.cpp -c -o ioaddr.o 

main: main.cpp
	g++ -g main.cpp -c -o main.o

clean:
	rm *.o program