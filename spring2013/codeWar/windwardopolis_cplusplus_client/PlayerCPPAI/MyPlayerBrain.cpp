#include "stdafx.h"
#include "MyPlayerBrain.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Linq;
using namespace System::Reflection;
using namespace PlayerCPPAI::api;
namespace PlayerCPPAI
{
	namespace AI
	{

		MyPlayerBrain::MyPlayerBrain(String ^name)
		{
			Name = !String::IsNullOrEmpty(name) ? name : NAME;
		}

		array<Byte> ^MyPlayerBrain::Avatar::get()
		{
			// bugbug replace the file MyAvatar.png in the solution and this will load it (32x32).
			//Project Properties > Linker > Input > Embed Managed Resource File
			Stream ^avatar = Assembly::GetExecutingAssembly()->GetManifestResourceStream("MyAvatar.png");
			try
			{
				if (avatar == nullptr) {
					if (log->IsDebugEnabled)
						log->Debug("No avatar file found.");
					return nullptr;
				}
				array<Byte> ^data = gcnew array<Byte>(avatar->Length);
				avatar->Read(data, 0, data->Length);
				return data;
			}
			finally
			{
				delete avatar;
			}
		}

		void MyPlayerBrain::Setup(Map ^map, Player ^me, List<Player^> ^players, List<Company^> ^companies, List<Passenger^> ^passengers, PlayerAIBase::PlayerOrdersEvent ^ordersEvent)
		{

			try
			{
				GameMap = map;
				Players = players;
				Me = me;
				Companies = companies;
				Passengers = passengers;
				sendOrders = ordersEvent;

				List<Passenger^> ^pickup = AllPickups(me, passengers);

				// get the path from where we are to the dest.
				List<Point> ^path = CalculatePathPlus1(me, pickup[0]->Lobby->BusStop);
				sendOrders("ready", path, pickup);
			}
			catch (Exception ^ex)
			{
				log->Fatal(String::Format("Setup({0}, ...", me == nullptr ? "{null}" : me->Name), ex);
			}
		}

		List<Company^>^ companiesNotEqualTo(Company^ cpy, List<Company^>^ companies) 
		{
			List<Company^>^ matches = gcnew List<Company^>;
			for each (Company^ c in companies)
				if (c != cpy)
					matches->Add(c);
			return matches;
		}
		
		generic<typename T>
		List<T>^ MyPlayerBrain::randomize(List<T>^ list)
		{
			for(int i = 0; i < list->Count; i++) {
				int indSwap = rand->Next() % list->Count;
				T temp = list[i];
				list[i] = list[indSwap];
				list[indSwap] = temp;
			}
			return list;
		}

		void MyPlayerBrain::GameStatus(PlayerAIBase::STATUS status, Player ^plyrStatus, List<Player^> ^players, List<Passenger^> ^passengers)
		{

			// bugbug - Framework.cs updates the object's in this object's Players, Passengers, and Companies lists. This works fine as long
			// as this app is single threaded. However, if you create worker thread(s) or respond to multiple status messages simultaneously
			// then you need to split these out and synchronize access to the saved list objects.

			try
			{
				// bugbug - we return if not us because the below code is only for when we need a new path or our limo hit a bus stop.
				// if you want to act on other players arriving at bus stops, you need to remove this. But make sure you use Me, not
				// plyrStatus for the Player you are updatiing (particularly to determine what tile to start your path from).
				if (plyrStatus != Me)
					return;

				Point ptDest;
				List<Passenger^> ^pickup = gcnew List<Passenger^>();
				switch (status)
				{
					case PlayerAIBase::STATUS::UPDATE:
						return;
					case PlayerAIBase::STATUS::NO_PATH:
					case PlayerAIBase::STATUS::PASSENGER_NO_ACTION:
						if (plyrStatus->Limo->Passenger == nullptr)
						{
							pickup = AllPickups(plyrStatus, passengers);
							ptDest = pickup[0]->Lobby->BusStop;
						}
						else
							ptDest = plyrStatus->Limo->Passenger->Destination->BusStop;
						break;
					case PlayerAIBase::STATUS::PASSENGER_DELIVERED:
					case PlayerAIBase::STATUS::PASSENGER_ABANDONED:
						pickup = AllPickups(plyrStatus, passengers);
						Trap::trap(pickup->Count == 0);
						ptDest = pickup[0]->Lobby->BusStop;
						break;
					case PlayerAIBase::STATUS::PASSENGER_REFUSED:
						ptDest = randomize(companiesNotEqualTo(plyrStatus->Limo->Passenger->Destination,Companies))[0]->BusStop;
						break;
					case PlayerAIBase::STATUS::PASSENGER_DELIVERED_AND_PICKED_UP:
					case PlayerAIBase::STATUS::PASSENGER_PICKED_UP:
						pickup = AllPickups(plyrStatus, passengers);
						ptDest = plyrStatus->Limo->Passenger->Destination->BusStop;
						break;
					default:
						throw gcnew ApplicationException("unknown status");
				}

				// get the path from where we are to the dest.
				List<Point> ^path = CalculatePathPlus1(plyrStatus, ptDest);

				if (log->IsDebugEnabled)
					log->Debug(String::Format("{0}; Path:{1}-{2}, {3} steps; Pickup:{4}, {5} total", status, path->Count > 0 ? path[0].ToString() : "{n/a}", path->Count > 0 ? path[path->Count - 1].ToString() : "{n/a}", path->Count, pickup->Count == 0 ? "{none}" : pickup[0]->Name, pickup->Count));

				// update our saved Player to match new settings
				if (path->Count > 0)
				{
					Me->Limo->Path->Clear();
					Me->Limo->Path->AddRange(path);
				}
				if (pickup->Count > 0)
				{
					Me->PickUp->Clear();
					Me->PickUp->AddRange(pickup);
				}

				sendOrders("move", path, pickup);
			}
			catch (Exception ^ex)
			{
				log->Error(String::Format("GameStatus({0}, {1}, ...", status, plyrStatus == nullptr ? "{null}" : plyrStatus->Name), ex);
			}
		}

		List<Point> ^MyPlayerBrain::CalculatePathPlus1(Player ^me, Point ptDest)
		{
			List<Point> ^path = SimpleAStar::CalculatePath(GameMap, me->Limo->TilePosition, ptDest);
			// add in leaving the bus stop so it has orders while we get the message saying it got there and are deciding what to do next.
			if (path->Count > 1)
				path->Add(path[path->Count - 2]);
			return path;
		}

		List<Passenger^> ^MyPlayerBrain::AllPickups(Player ^me, IEnumerable<Passenger^> ^passengers)
		{
			List<Passenger^> ^pickup = gcnew List<Passenger^>();
			for each (Passenger^ psngr in passengers)
				if (!me->PassengersDelivered->Contains(psngr) && (psngr != me->Limo->Passenger) && (psngr->Car == nullptr) && (psngr->Lobby != nullptr) && (psngr->Destination != nullptr))
					pickup->Add(psngr);

			pickup->AddRange(randomize(pickup));
			return pickup;
		}
	}
}
