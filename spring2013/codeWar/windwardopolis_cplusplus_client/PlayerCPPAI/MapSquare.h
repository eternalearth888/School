#pragma once

#include "Company.h"

using namespace System;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{
		public ref class MapSquare
		{
		public:
			// The direction of the road. Do not change these numbers, they are used as an index into an array.
			enum class DIRECTION
			{
				// Road running north/south.
				NORTH_SOUTH = 0,

				// Road running east/west.
				EAST_WEST = 1,

				// A 4-way intersection.
				INTERSECTION = 2,

				// A north/south road ended on the north side.
				NORTH_UTURN = 3,

				// An east/west road ended on the east side.
				EAST_UTURN = 4,

				// A north/south road ended on the south side.
				SOUTH_UTURN = 5,

				// An east/west road ended on the west side.
				WEST_UTURN = 6,

				// A T junction where the | of the T is entering from the north.
				T_NORTH = 7,

				// A T junction where the | of the T is entering from the east.
				T_EAST = 8,

				// A T junction where the | of the T is entering from the south.
				T_SOUTH = 9,

				// A T junction where the | of the T is entering from the west.
				T_WEST = 10,

				// A curve entered northward and exited eastward (or vice-versa).
				CURVE_NE = 11,

				// A curve entered northward and exited westward (or vice-versa).
				CURVE_NW = 12,

				// A curve entered southward and exited eastward (or vice-versa).
				CURVE_SE = 13,

				// A curve entered southward and exited westward (or vice-versa).
				CURVE_SW = 14,
			};

			// What type of square it is.
			enum class TYPE
			{
				// Park. Nothing on this, does nothing, cannot be driven on.
				PARK,

				// A road. The road DIRECTION determines which way cars can travel on the road.
				ROAD,

				// A company's bus stop. This is where passengers are loaded and unloaded.
				BUS_STOP,

				// Company building. Nothing on this, does nothing, cannot be driven on.
				COMPANY,
			};

			// Stop signs and signals for an intersection square.
			[Flags]
			enum class STOP_SIGNS
			{
				// No stop signs or signals.
				NONE = 0,
				// A stop entering from the North side.
				STOP_NORTH = 0x01,
				// A stop entering from the East side.
				STOP_EAST = 0x02,
				// A stop entering from the South side.
				STOP_SOUTH = 0x04,
				// A stop entering from the West side.
				STOP_WEST = 0x08
			};

			MapSquare(XmlElement ^elemTile);

			void ctor(Company ^company);

			// Settings for stop signs in this square. NONE for none.
			property STOP_SIGNS StopSigns;

			// The type of square.
			property bool Signal;

			// The type of square.
			property TYPE Type;

			// The company for this tile. Only set if a BUS_STOP.
			property Company ^Company;

			// True if the square can be driven on (ROAD or BUS_STOP).
			property bool IsDriveable
			{
				bool get();
			}

			// The direction of the road. This is only used for ROAD and BUS_STOP tiles.
			property DIRECTION Direction;

		};
	}
}
