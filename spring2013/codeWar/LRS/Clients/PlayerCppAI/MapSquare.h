#ifndef MAP_SQUARE_H
#define MAP_SQUARE_H

#include "Conveyor.h"
#include "Laser.h"
#include "MapSquareProperty.h"
#include "pugixml.hpp"

using pugi::xml_node;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// An individual square in the map.
		class MapSquare
		{
		public:
			MapSquare();
			/// element: Serialized XML of this object.
			MapSquare(const xml_node& element);
			MapSquare(const MapSquare& m);
			~MapSquare();
			
			MapSquareProperty::TYPE getType();
			
			// caller must not delete the pointer.
			vector<MapSquareProperty::SIDE>* getWalls();
			
			// caller must not delete the pointer.
			Conveyor* getConveyor();
			
			// caller must not delete the pointer.
			Laser* getLaser();
			
			int getFlag();

			MapSquare& operator=(const MapSquare& m);

		//protected:
			//void setType(MapSquareProperty::TYPE value);
			//void setWalls(vector<MapSquareProperty::SIDE> value);
			//void setConveyor(Conveyor* value);
			//void setLaser(Laser* value);
			//void setFlag(int value);

		private:
			/// The type of square.
			MapSquareProperty::TYPE m_type;
			/// What sides (if any) have walls.
			vector<MapSquareProperty::SIDE>* m_walls;
			/// The conveyor belt on this square. null if no conveyor.
			Conveyor* m_conveyor;
			/// The laser on this square. null if no laser.
			Laser* m_laser;
			/// The flag number (1..3) on this square. 0 if no flag.
			int m_flag;
		};
	}
}

#endif