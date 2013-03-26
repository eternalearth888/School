LIBS = /home/earth/Desktop/CS400_HW03

all: main

clean:
	rm main calc.o calc.tab.o
main: calc.o calc.tab.o
	gcc -o main calc.c calc.tab.c -I$(LIBS)
