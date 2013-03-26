#pragma once

#include "IPlayerAI.h"
#include "Map.h"
#include "Player.h"
#include "Company.h"
#include "Passenger.h"
#include "SimpleAStar.h"

// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

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
		// The sample C# AI. Start with this project but write your own code as this is a very simplistic implementation of the AI.
		public ref class MyPlayerBrain : IPlayerAI
		{
		private:
			// bugbug - put your team name here.
			literal String ^NAME = "Anders Hejlsberg";

			PlayerAIBase::PlayerOrdersEvent ^sendOrders;

			static initonly Random ^rand = gcnew Random();
			generic<typename T>
			static List<T>^ randomize(List<T>^ list);
			static initonly log4net::ILog ^log = log4net::LogManager::GetLogger(MyPlayerBrain::typeid);
			
			List<Point> ^CalculatePathPlus1(Player ^me, Point ptDest);

			static List<Passenger^> ^AllPickups(Player ^me, Collections::Generic::IEnumerable<Passenger^> ^passengers);

		public:
			// bugbug - put your school name here. Must be 11 letters or less (ie use MIT, not Massachussets Institute of Technology).
			literal String ^SCHOOL = "Windward U.";

			// The name of the player.
			property String ^Name;

			// The game map.
			property Map ^GameMap;

			// All of the players, including myself.
			property List<Player^> ^Players;

			// All of the companies.
			property List<Company^> ^Companies;

			// All of the passengers.
			property List<Passenger^> ^Passengers;

			// Me (my player object).
			property Player ^Me;

			MyPlayerBrain(String ^name);

			// The avatar of the player. Must be 32 x 32.
			property array<Byte> ^Avatar
			{
				array<Byte> ^get();
			}

			// Called at the start of the game.
			// map: The game map.
			// me: You. This is also in the players list.
			// players: All players (including you).
			// companies: The companies on the map.
			// passengers: The passengers that need a lift.
			// ordersEvent: Method to call to send orders to the server.
			virtual void Setup(Map ^map, Player ^me, List<Player^> ^players, List<Company^> ^companies, List<Passenger^> ^passengers, PlayerAIBase::PlayerOrdersEvent ^ordersEvent) sealed;

			// Called to send an update message to this A.I. We do NOT have to send orders in response.
			// status: The status message.
			// plyrStatus: The player this status is about. THIS MAY NOT BE YOU.
			// players: The status of all players.
			// passengers: The status of all passengers.
			virtual void GameStatus(PlayerAIBase::STATUS status, Player ^plyrStatus, List<Player^> ^players, List<Passenger^> ^passengers) sealed;
		};
	}
}
