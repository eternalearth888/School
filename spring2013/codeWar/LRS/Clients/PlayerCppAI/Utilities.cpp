#include <algorithm>
#include <iostream>
#include <sstream>
#include "PlayerCppAIException.h"
#include "Utilities.h"

using std::max;
using std::min;
using std::cout;
using std::endl;

using namespace PlayerCSharpAI::api;
namespace PlayerCSharpAI
{
	// MovePoint Begin

	Utilities::MovePoint::MovePoint() : location(NULL)
	{
		damage = 0;
		dead = false;
	}

	Utilities::MovePoint::MovePoint(BoardLocation* l)
	{
		location = l;
		damage = 0;
		dead = false;
	}

	Utilities::MovePoint::MovePoint(BoardLocation* l, int damage)
	{
		location = l;
		this->damage = damage;
	}

	Utilities::MovePoint::MovePoint(BoardLocation* l, bool dead)
	{
		location = l;
		this->dead = dead;
	}

	Utilities::MovePoint::MovePoint(const MovePoint& m)
	{
		if (m.location != NULL)
			location = new BoardLocation(*m.location);
		else
			location = NULL;
		dead = m.dead;
		damage = m.damage;
	}

	Utilities::MovePoint::~MovePoint()
	{
		delete location;
	}

	PlayerCSharpAI::api::BoardLocation* Utilities::MovePoint::getLocation()
	{
		return location;
	}

	void Utilities::MovePoint::setLocation(BoardLocation* l)
	{
		location = l;
	}

	int Utilities::MovePoint::getDamage()
	{
		return damage;
	}

	void Utilities::MovePoint::setDamage(int value)
	{
		damage = value;
	}

	bool Utilities::MovePoint::getDead()
	{
		return dead;
	}

	/*void Utilities::MovePoint::setDead(bool value)
	{
		dead = value;
	}*/

	// MovePoint End

	PlayerCSharpAI::Utilities::MovePoint* Utilities::CardDestination(GameMap& map, BoardLocation& startLocation, vector<Card>* cards)
	{
		vector<MovePoint>* points = CardPath(map, startLocation, cards);
		if (points == NULL || points->size() > 0)
			return new MovePoint(points->back());
		else
			return NULL;
	}

	vector<Utilities::MovePoint>* Utilities::CardPath(GameMap& map, BoardLocation& startLocation, vector<Card>* cards)
	{
		// if we can't move, we end up where we started
		vector<MovePoint>* points = new vector<MovePoint>;
		BoardLocation* curLoc = new BoardLocation(startLocation);
		points->push_back(MovePoint());
		points->back().setLocation(curLoc);

		for (vector<Card>::iterator cardOn = cards->begin(); cardOn != cards->end(); ++cardOn)
		{
			// move robot
			MovePoint* endLocation = Move(map, *curLoc, cardOn->getMove());
			if (endLocation->getDead())
			{
				points->push_back(MovePoint());
				points->back().setLocation(new BoardLocation(*endLocation->getLocation()));
				return points;
			}
			if (!(*endLocation->getLocation() == *curLoc))
			{
				curLoc = new BoardLocation(*endLocation->getLocation());
				points->push_back(MovePoint());
				points->back().setLocation(curLoc);
			}

			// conveyor belt - may cause a 1/4 turn.
			MapSquare* sq = map.GetSquare(curLoc->getMapPosition());
			for (int speed = 1; (sq->getConveyor() != NULL) && (speed <= sq->getConveyor()->getSpeed()); speed++)
			{
				delete endLocation;
				Point curLocPt = curLoc->getMapPosition();
				endLocation = Move(map, curLocPt, sq->getConveyor()->getDirection());
				BoardLocation* locMove = new BoardLocation(endLocation->getLocation()->getMapPosition(), curLoc->getDirection());
				sq = map.GetSquare(endLocation->getLocation()->getMapPosition());
				if (sq->getConveyor() != NULL)
				{
					Point endLocPt = endLocation->getLocation()->getMapPosition();
					MapSquareProperty::DIRECTION dirEnter = MoveDirection(curLocPt, endLocPt);
					BoardLocation* temp = locMove;
					locMove = locMove->Rotate(static_cast<int>(sq->getConveyor()->getDirection()) - static_cast<int>(dirEnter));
					delete temp;
				}
				curLoc = locMove;
				points->push_back(MovePoint());
				points->back().setLocation(curLoc);
			}

			// gears
			if (sq->getType() == MapSquareProperty::T_ROTATE_CLOCKWISE)
			{
				curLoc = curLoc->Rotate(1);
				points->push_back(MovePoint());
				points->back().setLocation(curLoc);
			}
			if (sq->getType() == MapSquareProperty::T_ROTATE_COUNTERCLOCKWISE)
			{
				curLoc = curLoc->Rotate(-1);
				points->push_back(MovePoint());
				points->back().setLocation(curLoc);
			}

			// damage
			int damage = CalcLaserDamage(map, *curLoc);
			if (damage != 0)
				points->back().setDamage(damage);
			delete endLocation;
		}

		return points;
	}

	int Utilities::CalcLaserDamage(GameMap& map, BoardLocation& location)
	{
		Point locPt = location.getMapPosition();
		int damage = 0;
		damage += _CalcLaserDamage(map, locPt, 0, -1, MapSquareProperty::D_SOUTH, MapSquareProperty::S_NORTH, MapSquareProperty::S_SOUTH);
		damage += _CalcLaserDamage(map, locPt, 0, 1, MapSquareProperty::D_NORTH, MapSquareProperty::S_SOUTH, MapSquareProperty::S_NORTH);
		damage += _CalcLaserDamage(map, locPt, -1, 0, MapSquareProperty::D_EAST, MapSquareProperty::S_WEST, MapSquareProperty::S_EAST);
		damage += _CalcLaserDamage(map, locPt, 1, 0, MapSquareProperty::D_WEST, MapSquareProperty::S_EAST, MapSquareProperty::S_WEST);
		return damage;
	}

	int Utilities::_CalcLaserDamage(GameMap& map, Point& position, int xAdd, int yAdd, MapSquareProperty::DIRECTION laserDirection, 
		MapSquareProperty::SIDE wallExit, MapSquareProperty::SIDE wallEnter)
	{
		int damage = 0;
		int x = position.X;
		int y = position.Y;
		bool startSquare = true;

		while ((0 <= x) && (x < map.getWidth()) && (0 <= y) && (y < map.getHeight()))
		{
			MapSquare* sq = &((*map.getSquares())[x][y]);
			// can we move into this square?
			//TODO: double-check this hitWall logic
			vector<MapSquareProperty::SIDE>* walls = sq->getWalls();
			bool hitWall = false;
			for (vector<MapSquareProperty::SIDE>::iterator it = walls->begin(); it != walls->end(); ++it)
				if (*it == wallEnter) {
					hitWall = true; 
					break;
				}
			if ((!startSquare) && hitWall)
				break;
			startSquare = false;

			if ((sq->getLaser() != 0) && (sq->getLaser()->getLocation()->getDirection() == laserDirection))
			{
				damage++;
				break;
			}

			// can we move out of this square?
			//TODO: double-check this hitWall logic
			walls = sq->getWalls();
			for (vector<MapSquareProperty::SIDE>::iterator it = walls->begin(); it != walls->end(); ++it)
				if (*it == wallExit) {
					hitWall = true;
					break;
				}
			if (hitWall)
				break;
			x += xAdd;
			y += yAdd;
		}
		return damage;
	}

	const MapSquareProperty::SIDE Utilities::sideMoveOut[4] = {MapSquareProperty::S_NORTH, MapSquareProperty::S_EAST, MapSquareProperty::S_SOUTH, MapSquareProperty::S_WEST};
	const MapSquareProperty::SIDE Utilities::sideMoveIn[4] = {MapSquareProperty::S_SOUTH, MapSquareProperty::S_WEST, MapSquareProperty::S_NORTH, MapSquareProperty::S_EAST};

	PlayerCSharpAI::Utilities::MovePoint* Utilities::Move(GameMap& map, BoardLocation& startLocation, Card::ROBOT_MOVE move)
	{
		int steps = 0;
		switch (move)
		{
		case Card::BACKWARD_ONE:
			steps = -1;
			break;
		case Card::FORWARD_ONE:
			steps = 1;
			break;
		case Card::FORWARD_TWO:
			steps = 2;
			break;
		case Card::FORWARD_THREE:
			steps = 3;
			break;
		case Card::ROTATE_LEFT:
			return new MovePoint(startLocation.Rotate(-1));
		case Card::ROTATE_RIGHT:
			return new MovePoint(startLocation.Rotate(1));
		case Card::ROTATE_UTURN:
			return new MovePoint(startLocation.Rotate(2));
		}

		BoardLocation* uturnLoc = startLocation.Rotate(2);
		MapSquareProperty::DIRECTION dir = steps >= 0 ? startLocation.getDirection() : uturnLoc->getDirection();
		delete uturnLoc;
		Point position = startLocation.getMapPosition();
		while (steps != 0)
		{
			MovePoint* mp = Move(map, position, dir);
			if (mp->getDead()) {
				Point p = mp->getLocation()->getMapPosition();
				delete mp;
				return new MovePoint(new BoardLocation(p, startLocation.getDirection()), true);
			}
			position = mp->getLocation()->getMapPosition();
			delete mp;
			int singleStep = max(-1, min(1, steps));
			steps -= singleStep;
		}
		return new MovePoint(new BoardLocation(position, startLocation.getDirection()));
	}

	PlayerCSharpAI::Utilities::MovePoint* Utilities::Move(GameMap& map, Point& position, MapSquareProperty::DIRECTION direction)
	{
		// watch for wall in this direction
		MapSquareProperty::SIDE sideExit = sideMoveOut[static_cast<int>(direction)];
		MapSquareProperty::SIDE sideEnter = sideMoveIn[static_cast<int>(direction)];
		BoardLocation* location = new BoardLocation(position, direction);

		// can we exit this square?
		MapSquare* sq = map.GetSquare(position);
		//TODO: double-check this hitWall logic
		vector<MapSquareProperty::SIDE>* walls = sq->getWalls();
		for (vector<MapSquareProperty::SIDE>::iterator it = walls->begin(); it != walls->end(); ++it)
			if (*it == sideExit) 
				return new MovePoint(location);
		BoardLocation* moveTo = location->Move(1);

		// did we go off the board?
		if ((moveTo->getMapPosition().X < 0) || (map.getWidth() <= moveTo->getMapPosition().X) || (moveTo->getMapPosition().Y < 0) || (map.getHeight() <= moveTo->getMapPosition().Y)) {
			delete moveTo;
			return new MovePoint(location, true);
		}

		// did we go into a pit?
		if (map.GetSquare(moveTo->getMapPosition())->getType() == MapSquareProperty::T_PIT) {
			delete location;
			return new MovePoint(moveTo, true);
		}

		// can we enter the new square?
		sq = map.GetSquare(moveTo->getMapPosition());
		walls = sq->getWalls();
		for (vector<MapSquareProperty::SIDE>::iterator it = walls->begin(); it != walls->end(); ++it)
			if (*it == sideEnter) {
				delete moveTo;
				return new MovePoint(location);
			}

		return new MovePoint(moveTo);
	}

	MapSquareProperty::DIRECTION Utilities::MoveDirection(Point& start, Point& end)
	{
		if (start.Y > end.Y)
			return MapSquareProperty::D_NORTH;
		if (start.Y < end.Y)
			return MapSquareProperty::D_SOUTH;
		if (start.X > end.X)
			return MapSquareProperty::D_WEST;
		if (start.X < end.X)
			return MapSquareProperty::D_EAST;

		std::stringstream out;
		out << "start = end point " << start.toStr();
		throw PlayerCppAIException(out.str().c_str());
	}
}
