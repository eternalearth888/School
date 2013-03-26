#ifndef BOARD_LOCATION_H
#define BOARD_LOCATION_H

#include <string>
#include <vector>
#include "MapSquareProperty.h"
#include "Point.h"
#include "pugixml.hpp"

using pugi::xml_node;
using pugi::xml_attribute;
using std::string;
using std::vector;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A location and direction on the board.
		class BoardLocation
		{
		public:
			BoardLocation();
			BoardLocation(const BoardLocation& b);
			// mapPosition: The board square loacted on.
			// direction: The direction pointed to on the board.
			BoardLocation(Point mapPosition, MapSquareProperty::DIRECTION direction);
			// Create from passed in XML.
			// element: Initialize with the values in this object.
			BoardLocation(const xml_node& element);
			
			// generates xml attributes.
			void makeAttributes(xml_node& parent);

			/// The location on the map for this unit. Generally (-1, -1) if the unit is dead.
			Point getMapPosition() const;
			void setMapPosition(Point value);

			/// The direction this unit is facing. Ignored if the unit is dead.
			MapSquareProperty::DIRECTION getDirection() const;
			void setDirection(MapSquareProperty::DIRECTION value);

			/// Return a new BoardLocation moved the requested number of squares in the location's direction. This can move off the 
			/// board and is not blocked by units or walls.
			/// Caller responsible for deleting the pointer.
			/// num: The number of map squares to move.
			BoardLocation* Move(int num) const;

			/// Rotate the direction in a clockwise direction (NESW) the number of turns requested. A value of 4 results in a full circle.
			/// Caller responsible for deleting the pointer.
			/// num: The number of quarter turns to make. Can be negative or positive. Can be outside the range of -3 .. 3.
			/// returns: A new struct at the location turned to.
			BoardLocation* Rotate(int num) const;

			/// Equality operator.
			/// obj: The BoardLocation to compare to.
			/// returns: true if both objects are at the same position in the same direction.
			bool operator==(const BoardLocation& loc) const;

			string toStr() const;
			
		private:
			Point m_mapPos;
			MapSquareProperty::DIRECTION m_dir;
		};
	}
}

#endif