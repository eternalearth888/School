#ifndef MAP_SQUARE_PROPERTY_H
#define MAP_SQUARE_PROPERTY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace MapSquareProperty
{
	/// The direction a robot or laser is facing. ALso used for direction a conveyor is running (exit for a turn).
	enum DIRECTION
	{
		/// Facing North and can fire on units above.
		D_NORTH = 0,
		/// Facing East and can fire on units to the right.
		D_EAST = 1,
		/// Facing South and can fire on units below.
		D_SOUTH = 2,
		/// Facing West and can fire on units to the left.
		D_WEST = 3
	};

	/// Which side(s) of the square have a wall. A square can have multiple walls.
	enum SIDE
	{
		/// No walls.
		S_NONE = 0,
		/// A wall on the North (top) side.
		S_NORTH = 0x01,
		/// A wall on the East (right) side.
		S_EAST = 0x02,
		/// A wall on the South (bottom) side.
		S_SOUTH = 0x04,
		/// A wall on the West (left) side.
		S_WEST = 0x08
	};

	/// What type of square it is.
	enum TYPE
	{
		/// Normal - nothing on it.
		T_NORMAL,
		/// Has a conveyor belt on it.
		T_CONVEYOR_BELT,
		/// Is a gear that rotates clockwise.
		T_ROTATE_CLOCKWISE,
		/// Is a gear that rotates counter-clockwise.
		T_ROTATE_COUNTERCLOCKWISE,
		/// Is a repair square.
		T_REPAIR,
		/// Is a flag.
		T_FLAG,
		// Is a pit.
		T_PIT
	};

	DIRECTION parseDirection(const char* value);
	SIDE parseSideSingle(const char* value);
	// caller is responsible for deleting the pointer.
	vector<SIDE>* parseSide(const char* value);
	TYPE parseType(const char* value);

	string str(DIRECTION);
	string str(SIDE);
	string str(const vector<SIDE>&);
	string str(TYPE);
}

#endif