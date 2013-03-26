#include <cstdlib>
#include <cstring>
#include "PlayerCppAIException.h"
#include "MapSquareProperty.h"

using std::exception;
using std::strcpy;
using std::strlen;
using std::strtok;

MapSquareProperty::DIRECTION MapSquareProperty::parseDirection(const char* value)
{
	if (strcmp(value, "NORTH") == 0)
		return D_NORTH;
	if (strcmp(value, "EAST") == 0)
		return D_EAST;
	if (strcmp(value, "SOUTH") == 0) 
		return D_SOUTH;
	if (strcmp(value, "WEST") == 0)
		return D_WEST;
	
	throw PlayerCppAIException("invalid direction");
}

MapSquareProperty::SIDE MapSquareProperty::parseSideSingle(const char* value)
{
	if (strcmp(value, "NONE") == 0)
		return S_NONE;
	if (strcmp(value, "NORTH") == 0)
		return S_NORTH;
	if (strcmp(value, "EAST") == 0)
		return S_EAST;
	if (strcmp(value, "SOUTH") == 0)
		return S_SOUTH;
	if (strcmp(value, "WEST") == 0)
		return S_WEST;

	throw PlayerCppAIException("invalid side");
}

vector<MapSquareProperty::SIDE>* MapSquareProperty::parseSide(const char* value)
{
	char* s = new char[strlen(value)];
	strcpy(s, value);
	char* delims = ", ";
	char* tok(NULL);
	tok = strtok(s, delims);
	vector<MapSquareProperty::SIDE>* sides = new vector<MapSquareProperty::SIDE>;
	while (tok != NULL)
	{
		sides->push_back(parseSideSingle(tok));
		tok = strtok(NULL, delims);
	}
	return sides;
}

MapSquareProperty::TYPE MapSquareProperty::parseType(const char* value)
{
	if (strcmp(value, "NORMAL") == 0)
		return T_NORMAL;
	if (strcmp(value, "CONVEYOR_BELT") == 0)
		return T_CONVEYOR_BELT;
	if (strcmp(value, "ROTATE_CLOCKWISE") == 0)
		return T_ROTATE_CLOCKWISE;
	if (strcmp(value, "ROTATE_COUNTERCLOCKWISE") == 0)
		return T_ROTATE_COUNTERCLOCKWISE;
	if (strcmp(value, "REPAIR") == 0)
		return T_REPAIR;
	if (strcmp(value, "FLAG") == 0)
		return T_FLAG;
	if (strcmp(value, "PIT") == 0)
		return T_PIT;

	throw PlayerCppAIException("invalid type");
}

string MapSquareProperty::str(DIRECTION d) {
	switch (d)
	{
	case D_NORTH:
		return "NORTH";
	case D_EAST:
		return "EAST";
	case D_SOUTH:
		return "SOUTH";
	case D_WEST:
		return "WEST";
	default:
		throw PlayerCppAIException("invalid direction");
	}
}

string MapSquareProperty::str(SIDE s) 
{
	switch (s)
	{
	case S_NONE:
		return "NONE";
	case S_NORTH:
		return "NORTH";
	case S_EAST:
		return "EAST";
	case S_SOUTH:
		return "SOUTH";
	case S_WEST:
		return "WEST";
	default:
		throw PlayerCppAIException("invalid side");
	}
}

string MapSquareProperty::str(const vector<SIDE>& sides)
{
	string s = "";
	for (vector<SIDE>::const_iterator it = sides.begin(); it != sides.end(); ++it)
	{
		s += str(*it);
		if (it != sides.end() - 1)
			s+= ", ";
	}
	return s;
}

string MapSquareProperty::str(TYPE t) 
{
	switch (t)
	{
	case T_NORMAL:
		return "NORMAL";
	case T_CONVEYOR_BELT:
		return "CONVEYER_BELT";
	case T_ROTATE_CLOCKWISE:
		return "ROTATE_CLOCKWISE";
	case T_ROTATE_COUNTERCLOCKWISE:
		return "ROTATE_COUNTERCLOCKWISE";
	case T_REPAIR:
		return "REPAIR";
	case T_FLAG:
		return "FLAG";
	case T_PIT:
		return "PIT";
	default:
		throw PlayerCppAIException("invalid type");
	}
}
