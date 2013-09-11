iofile.o: IOFile.cpp iofile.h
	g++ -Wall -g -c IOFile.cpp

manip.o: Manip.cpp Manip.h
	g++ -Wall -g -c Manip.cpp

main.o: main.cpp iofile.h Manip.h
	g++ -Wall -g -c main.cpp

mkarkm: main.o iofile.o manip.o
	g++ -g iofile.o mainp.o main.o -lm -o mkarkm
