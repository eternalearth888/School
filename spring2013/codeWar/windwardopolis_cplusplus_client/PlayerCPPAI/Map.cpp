#include "stdafx.h"
#include "Map.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;
namespace PlayerCPPAI
{
	namespace api
	{

		Map::Map(XmlElement ^elemMap, List<Company^> ^companies)
		{
			int width = Convert::ToInt32(elemMap->GetAttribute("width"));
			int height = Convert::ToInt32(elemMap->GetAttribute("height"));
			UnitsPerTile = Convert::ToInt32(elemMap->GetAttribute("units-tile"));

			Squares = gcnew array<array<MapSquare^>^>(width);
			for (int x = 0; x < width; x++)
				Squares[x] = gcnew array<MapSquare^>(height);

			for each (XmlElement ^elemTile in elemMap->SelectNodes("tile"))
			{
				int x = Convert::ToInt32(elemTile->GetAttribute("x"));
				int y = Convert::ToInt32(elemTile->GetAttribute("y"));
				Squares[x][y] = gcnew MapSquare(elemTile);
			}

			for each (Company^ cmpyOn in companies)
				Squares[cmpyOn->BusStop.X][cmpyOn->BusStop.Y]->ctor(cmpyOn);
		}

		int Map::Width::get()
		{
			return Squares->Length;
		}

		int Map::Height::get()
		{
			return Squares[0]->Length;
		}

		PlayerCPPAI::api::MapSquare ^Map::SquareOrDefault(Point pt)
		{
			if ((pt.X < 0) || (pt.Y < 0) || (pt.X >= Width) || (pt.Y >= Height))
				return nullptr;
			return Squares[pt.X][pt.Y];
		}
	}
}
