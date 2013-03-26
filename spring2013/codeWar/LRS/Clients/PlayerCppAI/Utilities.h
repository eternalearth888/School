#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include "BoardLocation.h"
#include "Card.h"
#include "GameMap.h"
#include "MapSquareProperty.h"
#include "Trap.h"

using std::vector;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{
	/// Utilities that can be of use to an AI.
	class Utilities
	{
	public:
		class MovePoint
		{
		public:
			MovePoint();
			/// Create the object. No damage and not dead.
			/// l: The location of the move result.
			MovePoint(BoardLocation* l);
			/// Create the object. Not dead.
			/// l: The location of the move result.
			/// damage: The damage level from this move.
			MovePoint(BoardLocation* l, int damage);
			/// Create the object. No damage.
			/// l: The location of the move result.
			/// dead: true if the move caused death.
			MovePoint(BoardLocation* l, bool dead);
			MovePoint(const MovePoint& m);
			~MovePoint();

			// Gets the BoardLocation. Caller must not delete the pointer.
			BoardLocation* getLocation();
			void setLocation(BoardLocation* l);

			int getDamage();
			void setDamage(int value);

			bool getDead();

		private:
			//void setLocation(BoardLocation* value);

			//void setDead(bool value);

			/// The location of the move result.
			BoardLocation* location;
			/// The damage level received from this move.
			int damage;
			/// true if the move caused the unit to die (moved off the board).
			bool dead;
		};

		// Destination for a movement. Ignores all robots on the map but does take into account walls, conveyor belts and gears. Returns
		// the final location of the move.
		// Caller responsible for deleting the pointer.
		// map: The game map.
		// startLocation: Where the unit starts.
		// cards: The cards to apply.
		// return: The final location of the move.
		static MovePoint* CardDestination(GameMap& map, BoardLocation& startLocation, vector<Card>* cards);

		/// Destination for a movement. Ignores all robots on the map but does take into account walls, conveyor belts and gears. Returns
		/// every step of the move.
		/// Caller is responsible for deleting the pointer.
		/// map: The game map.
		/// startLocation: Where the unit starts.
		/// cards: The cards to apply.
		/// return: Every step of the move.
		static vector<MovePoint>* CardPath(GameMap& map, BoardLocation& startLocation, vector<Card>* cards);

		/// Calculates what damage a unit will receive from lasers at a given location.
		/// map: The game map.
		/// location: Where the unit is located.
		/// return: The amount of damage. Will be 0 or 1.
		static int CalcLaserDamage(GameMap& map, BoardLocation& location);
		
		/// Move a unit one card move. Ignores all robots on the map but does take into account walls, conveyor belts and gears.
		/// Caller is responsible for deleting the pointer.
		/// map: The game map.
		/// startLocation: Where the unit starts.
		/// move: The move to apply.
		/// return: The final location of the move.
		static MovePoint* Move(GameMap& map, BoardLocation& startLocation, Card::ROBOT_MOVE move);

		/// Move a unit one square in the requested direction. Ignores all robots on the map but does take into account walls, conveyor belts and gears.
		/// map: The game map.
		/// position: The map square to start the move from.
		/// direction: The direction to move.
		/// return: The final location of the move.
		static MovePoint* Move(GameMap& map, Point& position, MapSquareProperty::DIRECTION direction);

		static MapSquareProperty::DIRECTION MoveDirection(Point& start, Point& end);

	private:
		static int _CalcLaserDamage(GameMap& map, Point& position, int xAdd, int yAdd, MapSquareProperty::DIRECTION laserDirection, 
			MapSquareProperty::SIDE wallExit, MapSquareProperty::SIDE wallEnter);

		// NESW
		static const MapSquareProperty::SIDE sideMoveOut[4];
		static const MapSquareProperty::SIDE sideMoveIn[4];
	};
}

#endif