image.o: image.cpp image.h
	g++ -Wall -g -c image.cpp

main.o: main.cpp
	g++ -Wall -g -c main.cpp

nalene: image.o main.o
	g++ -f image.o main.o -lm -o nalene
