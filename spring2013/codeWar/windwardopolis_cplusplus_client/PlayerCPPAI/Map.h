#pragma once

#include "Company.h"
#include "MapSquare.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{
		public ref class Map
		{
		public:
			Map(XmlElement ^elemMap, List<Company^> ^companies);

			// The map squares. This is in the format [x][y].
			property array<array<MapSquare^>^> ^Squares;

			// The number of map units in a tile. Some points are in map units and
			/// some are in tile units.
			property int UnitsPerTile;

			// The width of the map. Units are squares.
			property int Width
			{
				int get();
			}

			// The height of the map. Units are squares.
			property int Height
			{
				int get();
			}

			// Returns the requested point or null if off the map.
			MapSquare ^SquareOrDefault(Point pt);
		};
	}
}
