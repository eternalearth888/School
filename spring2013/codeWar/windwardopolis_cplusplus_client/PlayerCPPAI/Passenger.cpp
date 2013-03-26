#include "stdafx.h"
#include "Passenger.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml;
namespace PlayerCPPAI
{
	namespace api
	{
		Passenger::Passenger(XmlElement ^elemPassenger, List<Company^> ^companies)
		{
			Name = elemPassenger->GetAttribute("name");
			PointsDelivered = Convert::ToInt32(elemPassenger->GetAttribute("points-delivered"));
			XmlAttribute ^attr = elemPassenger->GetAttributeNode("lobby");
			if (attr != nullptr)
				Lobby = findCompany(companies, attr->Value);
			attr = elemPassenger->GetAttributeNode("destination");
			if (attr != nullptr)
				Destination = findCompany(companies, attr->Value);
			Route = gcnew List<Company^>();
			for each (XmlElement ^elemRoute in elemPassenger->GetElementsByTagName("route"))
				Route->Add(findCompany(companies, elemRoute->InnerText));
			Enemies = gcnew List<Passenger^>();
		}

		List<Passenger^> ^Passenger::FromXml(XmlElement ^elemPassengers, List<Company^> ^companies)
		{
			List<Passenger^> ^passengers = gcnew List<Passenger^>();
			for each (XmlElement ^elemPsngrOn in elemPassengers->GetElementsByTagName("passenger"))
				passengers->Add(gcnew Passenger(elemPsngrOn, companies));

			// need to now assign enemies - needed all Passenger objects created first.
			for each (XmlElement ^elemPsngrOn in elemPassengers->GetElementsByTagName("passenger"))
			{
				Passenger ^psngrOn = findPassenger(passengers, elemPsngrOn->GetAttribute("name"));
				for each (XmlElement ^elemEnemyOn in elemPsngrOn->GetElementsByTagName("enemy"))
					psngrOn->Enemies->Add(findPassenger(passengers, elemEnemyOn->InnerText));
			}

			// set if they're in a lobby
			for each (Passenger ^psngrOn in passengers)
			{
				if (psngrOn->Lobby == nullptr)
					continue;
				psngrOn->Lobby->Passengers->Add(psngrOn);
			}

			return passengers;
		}

		void Passenger::UpdateFromXml(List<Passenger^> ^passengers, List<Company^> ^companies, XmlElement ^elemPassengers)
		{
			for each (XmlElement ^elemPsngrOn in elemPassengers->GetElementsByTagName("passenger"))
			{
				Passenger ^psngrOn = findPassenger(passengers, elemPsngrOn->GetAttribute("name"));
				XmlAttribute ^attr = elemPsngrOn->GetAttributeNode("destination");
				if (attr != nullptr)
				{
					psngrOn->Destination = findCompany(companies, attr->Value);
					// remove from the route
					if (psngrOn->Route->Contains(psngrOn->Destination))
						psngrOn->Route->Remove(psngrOn->Destination);
				}

				// set props based on waiting, travelling, done
				if (elemPsngrOn->GetAttribute("status")->Equals("lobby")) {
						psngrOn->Lobby = findCompany(companies, elemPsngrOn->GetAttribute("lobby"));
						psngrOn->Car = nullptr;
				}
				else if (elemPsngrOn->GetAttribute("status")->Equals("travelling")) {
						psngrOn->Lobby = nullptr;
						// psngrOn.Car set in Player update.
				}
				else if (elemPsngrOn->GetAttribute("status")->Equals("done")) {
						Trap::trap();
						psngrOn->Destination = nullptr;
						psngrOn->Lobby = nullptr;
						psngrOn->Car = nullptr;
				}
			}
		}

		String ^Passenger::ToString()
		{
			return Name;
		}
	}
}
