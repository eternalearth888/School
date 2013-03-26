#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace PlayerCPPAI
{
	namespace api
	{
		ref class Passenger;

		public ref class Limo
		{
		public:
			// Create the object.
			// tilePosition: The location in tile units of the center of the vehicle.
			// angle: The Angle this unit is facing.
			Limo(Point tilePosition, int angle);

			// The location in tile units of the center of the vehicle.
			property Point TilePosition;

			// 0 .. 359 The Angle this unit is facing. 0 is North and 90 is East.
			property int Angle;

			// The passenger in this limo. null if no passenger.
			property Passenger ^Passenger;

			// Only set for the AI's own Limo - the number of tiles remaining in the Limo's path.
			/// This may be wrong after movement as all we get is a count. This is updated with the
			/// most recent list sent to the server.
			property List<Point> ^Path;

			virtual String ^ToString() override;
		};
	}
}
