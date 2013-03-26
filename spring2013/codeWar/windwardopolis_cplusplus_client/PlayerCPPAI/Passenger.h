#pragma once

#include "Company.h"
#include "Limo.h"
#include "Trap.h"
#include "Util.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{
		public ref class Passenger
		{
		private:
			Passenger(XmlElement ^elemPassenger, List<Company^> ^companies);

		public:
			// The name of this passenger.
			property String ^Name;

			// The number of points a player gets for delivering this passenger.
			property int PointsDelivered;

			// The limo the passenger is presently in. null if not in a limo.
			property Limo ^Car;

			// The bus stop the passenger is presently waiting in. null if in a limo or has arrived at final destination.
			property Company ^Lobby;

			// The company the passenger wishes to go to. This is valid both at a bus stop and in a car. It is null if
			// they have been delivered to their final destination.
			property Company ^Destination;

			// The remaining companies the passenger wishes to go to after destination, in order. This does not include
			// the Destination company.
			property Collections::Generic::IList<Company^> ^Route;

			// If any of these passengers are at a bus stop, this passenger will not exit the car at the bus stop.
			// If a passenger at the bus stop has this passenger as an enemy, the passenger can still exit the car.
			property Collections::Generic::IList<Passenger^> ^Enemies;

			static List<Passenger^> ^FromXml(XmlElement ^elemPassengers, List<Company^> ^companies);

			static void UpdateFromXml(List<Passenger^> ^passengers, List<Company^> ^companies, XmlElement ^elemPassengers);

			virtual String ^ToString() override;
		};
	}
}
