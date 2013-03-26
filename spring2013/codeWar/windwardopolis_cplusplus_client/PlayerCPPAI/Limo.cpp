#include "stdafx.h"
#include "Limo.h"
#include "Passenger.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
namespace PlayerCPPAI
{
	namespace api
	{

		Limo::Limo(Point tilePosition, int angle)
		{
			TilePosition = tilePosition;
			Angle = angle;
			Path = gcnew List<Point>();
		}

		String ^Limo::ToString()
		{
			if (Passenger != nullptr)
				return String::Format("{0}:{1}; Passenger:{2}; Dest:{3}; PathLength:{4}", TilePosition, Angle, Passenger == nullptr ? "{none}" : Passenger->Name, 
					Passenger->Destination, Path->Count);
			return String::Format("{0}:{1}; Passenger:{2}", TilePosition, Angle, Passenger == nullptr ? "{none}" : Passenger->Name);
		}
	}
}
