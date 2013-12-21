all: main

clean:
	rm  main main.o sqlite3.o

main:    main.o sqlite3.o
	g++ -c -o main.o main.cpp
	gcc -c -o sqlite3.o sqlite3.c
	g++ -o main sqlite3.o main.o -lpthread -ldl
