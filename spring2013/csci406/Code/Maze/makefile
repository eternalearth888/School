main: mazeMain.o mazeEdge.o
	g++ -o main mazeMain.o mazeEdge.o

mazeMain.o: mazeMain.cpp
	g++ -c mazeMain.cpp

mazeEdge.o: mazeEdge.cpp mazeEdge.h
	g++ -c mazeEdge.cpp

clean:
	rm main mazeEdge.o mazeMain.o
