#include "stdafx.h"
#include "Player.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{

		Player::Player(XmlElement ^elemPlayer)
		{
			Guid = elemPlayer->GetAttribute("guid");
			Name = elemPlayer->GetAttribute("name");
			this->Limo = gcnew api::Limo(Point(Convert::ToInt32(elemPlayer->GetAttribute("limo-x")), Convert::ToInt32(elemPlayer->GetAttribute("limo-y"))), Convert::ToInt32(elemPlayer->GetAttribute("limo-angle")));
			PickUp = gcnew List<Passenger^>();
			PassengersDelivered = gcnew List<Passenger^>();
		}

		List<Player^> ^Player::FromXml(XmlElement ^elemPlayers)
		{
			List<Player^> ^players = gcnew List<Player^>();
			for each (XmlElement ^elemPlyrOn in elemPlayers->SelectNodes("player"))
				players->Add(gcnew Player(elemPlyrOn));
			return players;
		}

		void Player::UpdateFromXml(List<Player^> ^players, List<Passenger^> ^passengers, XmlElement ^elemPlayers)
		{
			for each (XmlElement ^elemPlyrOn in elemPlayers->SelectNodes("player"))
			{
				Player ^plyrOn = findPlayer(players, elemPlyrOn->GetAttribute("guid"));

				plyrOn->Score = Convert::ToSingle(elemPlyrOn->GetAttribute("score"));

				// car location
				plyrOn->Limo->TilePosition = Point(Convert::ToInt32(elemPlyrOn->GetAttribute("limo-x")), Convert::ToInt32(elemPlyrOn->GetAttribute("limo-y")));
				plyrOn->Limo->Angle = Convert::ToInt32(elemPlyrOn->GetAttribute("limo-angle"));

				// see if we now have a passenger.
				XmlAttribute ^attrPassenger = elemPlyrOn->GetAttributeNode("passenger");
				if (attrPassenger != nullptr)
				{
					Passenger ^passenger = findPassenger(passengers, attrPassenger->Value);
					plyrOn->Limo->Passenger = passenger;
					passenger->Car = plyrOn->Limo;
				}
				else
					plyrOn->Limo->Passenger = nullptr;

				// add most recent delivery if we this is the first time we're told.
				attrPassenger = elemPlyrOn->GetAttributeNode("last-delivered");
				if (attrPassenger != nullptr)
				{
					Passenger ^passenger = findPassenger(passengers, attrPassenger->Value);
					if (!plyrOn->PassengersDelivered->Contains(passenger))
						plyrOn->PassengersDelivered->Add(passenger);
				}
			}
		}

		String ^Player::ToString()
		{
			return String::Format("{0}; NumDelivered:{1}", Name, PassengersDelivered->Count);
		}
	}
}
