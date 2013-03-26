#ifndef CONVEYER_H
#define CONVEYER_H

#include "MapSquareProperty.h"
#include "pugixml.hpp"

using pugi::xml_node;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A converyor belt. This is an element of a map square and represents the conveyor belt on that single square.
		class Conveyor
		{
		public:
			/// Build from XML serialization of this object.
			/// element: Initialize with the values in this object.
			Conveyor(const xml_node& element);
			
			int getSpeed() const;
			void setSpeed(int value);

			MapSquareProperty::DIRECTION getDirection() const;
			void setDirection(MapSquareProperty::DIRECTION value);
			
			MapSquareProperty::SIDE getEntry() const;
			void setEntry(MapSquareProperty::SIDE value);

		private:
			/// The speed of the belt. Values are 1 or 2.
			int m_speed;
			/// The direction the belt exits at.
			MapSquareProperty::DIRECTION m_direction;
			/// The direction(s) the converyor belt enters from.
			MapSquareProperty::SIDE m_entry;
		};
	}
}

#endif