#ifndef LASER_H
#define LASER_H

#include "CombatUnit.h"
#include "pugixml.hpp"

using pugi::xml_node;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A laser on the board. This sits on a specific map square.
		class Laser : public CombatUnit
		{
		public:
			Laser();
			/// element: Initialize with the values in this XML.
			Laser(const xml_node& element);
			Laser(const Laser& l);
			
			int getNumSquares() const;

			Laser& operator=(const Laser& l);

		private:
			//void setNumSquares(int value);

			/// The number of squares the laser shoots over, including the one it is on. (The Laser is ended by a wall.)
			int m_numSquares;
		};
	}
}

#endif