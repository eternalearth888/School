LIBS = /home/earth/Documents/school/spring2013/csci400/CS400_MDESLIS_HW09

all: main

clean:
	rm -f main lex.yy.o simpleCalc.tab.o lex.yy.c simpleCalc.tab.c simpleCalc.tab.h

simpleCalc.tab.c simpleCalc.tab.h: simpleCalc.y
	bison simpleCalc.y

lex.yy.c: simpleCalc.l simpleCalc.tab.h
	flex simpleCalc.l

main: lex.yy.o simpleCalc.tab.o
	gcc -o main lex.yy.o simpleCalc.tab.o -lm -I$(LIBS)
