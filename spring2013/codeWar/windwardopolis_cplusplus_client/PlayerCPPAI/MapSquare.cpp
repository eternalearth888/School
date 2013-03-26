#include "stdafx.h"
#include "MapSquare.h"

using namespace System;
using namespace System::Xml;
namespace PlayerCPPAI
{
	namespace api
	{

		MapSquare::MapSquare(XmlElement ^elemTile)
		{
			Type = safe_cast<TYPE>(Enum::Parse(TYPE::typeid, elemTile->GetAttribute("type")));
			if (IsDriveable)
			{
				Direction = safe_cast<DIRECTION>(Enum::Parse(DIRECTION::typeid, elemTile->GetAttribute("direction")));
				XmlAttribute ^attr = elemTile->GetAttributeNode("stop-sign");
				StopSigns = attr == nullptr ? STOP_SIGNS::NONE : safe_cast<STOP_SIGNS>(Enum::Parse(STOP_SIGNS::typeid, attr->Value));
				attr = elemTile->GetAttributeNode("signal");
				Signal = attr != nullptr && attr->Value->ToLower() == "true";
			}
		}

		void MapSquare::ctor(api::Company ^company)
		{
			Company = company;
		}

		bool MapSquare::IsDriveable::get()
		{
			return Type == TYPE::ROAD || Type == TYPE::BUS_STOP;
		}
	}
}
