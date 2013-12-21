pcppai: main.o Framework.o cencode.o pugixml.o MyPlayerBrain.o Point.o BoardLocation.o Card.o GameMap.o MapSquare.o Conveyor.o Laser.o CombatUnit.o Image.o Player.o FlagState.o Robot.o PlayerTurn.o Utilities.o Trap.o MapSquareProperty.o TcpClient.o FifoBuffer.o EncodingMock.o
	g++ -o pcppai main.o Framework.o cencode.o pugixml.o MyPlayerBrain.o Point.o BoardLocation.o Card.o GameMap.o MapSquare.o Conveyor.o Laser.o CombatUnit.o Image.o Player.o FlagState.o Robot.o PlayerTurn.o Utilities.o Trap.o MapSquareProperty.o TcpClient.o FifoBuffer.o EncodingMock.o -lboost_thread -lboost_system

main.o: main.cpp Framework.h
	g++ -c main.cpp

Framework.o: Framework.h Framework.cpp IPlayerCallback.h MyPlayerBrain.h Point.h TcpClient.h encode.h
	g++ -c Framework.cpp

cencode.o: encode.h cencode.h cencode.c
	gcc -c cencode.c

pugixml.o: pugixml.hpp pugixml.cpp
	g++ -c pugixml.cpp

MyPlayerBrain.o: MyPlayerBrain.h MyPlayerBrain.cpp BoardLocation.h Card.h GameMap.h Image.h Player.h PlayerTurn.h Point.h Utilities.h
	g++ -c MyPlayerBrain.cpp

Point.o: Point.h Point.cpp
	g++ -c Point.cpp

BoardLocation.o: BoardLocation.h BoardLocation.cpp MapSquareProperty.h Point.h
	g++ -c BoardLocation.cpp

Card.o: Card.h Card.cpp
	g++ -c Card.cpp

GameMap.o: GameMap.h GameMap.cpp MapSquare.h Point.h
	g++ -c GameMap.cpp

MapSquare.o: MapSquare.h MapSquare.cpp Conveyor.h Laser.h MapSquareProperty.h
	g++ -c MapSquare.cpp

Conveyor.o: Conveyor.h Conveyor.cpp MapSquareProperty.h
	g++ -c Conveyor.cpp

Laser.o: Laser.h Laser.cpp CombatUnit.h 
	g++ -c Laser.cpp

CombatUnit.o: CombatUnit.h CombatUnit.cpp BoardLocation.h
	g++ -c CombatUnit.cpp

Image.o: Image.h Image.cpp
	g++ -c Image.cpp

Player.o: Player.h Player.cpp Card.h FlagState.h PlayerCppAIException.h Point.h Robot.h
	g++ -c Player.cpp

FlagState.o: FlagState.h FlagState.cpp Point.h
	g++ -c FlagState.cpp

Robot.o: Robot.h Robot.cpp CombatUnit.h
	g++ -c Robot.cpp

PlayerTurn.o: PlayerTurn.h PlayerTurn.cpp Card.h
	g++ -c PlayerTurn.cpp

Utilities.o: Utilities.h Utilities.cpp BoardLocation.h Card.h GameMap.h MapSquareProperty.h PlayerCppAIException.h Trap.h
	g++ -c Utilities.cpp

Trap.o: Trap.h Trap.cpp
	g++ -c Trap.cpp

MapSquareProperty.o: MapSquareProperty.h MapSquareProperty.cpp PlayerCppAIException.h
	g++ -c MapSquareProperty.cpp

TcpClient.o: TcpClient.h TcpClient.cpp EncodingMock.h FifoBuffer.h IPlayerCallback.h PlayerCppAIException.h Trap.h
	g++ -c TcpClient.cpp

EncodingMock.o: EncodingMock.h EncodingMock.cpp
	g++ -c EncodingMock.cpp

FifoBuffer.o: FifoBuffer.h FifoBuffer.cpp PlayerCppAIException.h
	g++ -c FifoBuffer.cpp

clean:
	rm -f *.o pcppai
