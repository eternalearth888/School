#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>

#include "MapSquare.h"
#include "Point.h"
#include "pugixml.hpp"

using pugi::xml_node;
using std::vector;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// The map of the game.
		class GameMap
		{
		public:
			/// Create the map from the passed across XML
			/// element: The parent map node.
			GameMap(const xml_node& element);
			~GameMap();

			/// The width of the map. Units are squares.
			int getWidth();
			/// The height of the map. Units are squares.
			int getHeight();

			// caller must not delete the pointer.
			vector< vector<MapSquare> >* getSquares();
			
			// caller must not delete the pointer.
			vector<Point>* getFlags();

			/// Get a specific map square.
			/// Caller must not delete the pointer.
			/// location: The x, y point for the square desired.
			MapSquare* GetSquare(Point location);

		//protected:
			//void setSquares(vector<vector<MapSquare>> value);
			//void setFlags(vector<Point> value);

		private:
			/// The map squares. This is in the format [x][y].
			vector< vector<MapSquare> >* m_squares;
			/// Location (map squares) of the flags in order.
			vector<Point>* m_flags;
		};
	}
}

#endif
