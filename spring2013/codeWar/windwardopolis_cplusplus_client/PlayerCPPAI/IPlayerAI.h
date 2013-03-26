#pragma once

using namespace System;

#include "Map.h"
#include "Passenger.h"
#include "Player.h"
#include "Company.h"

using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace PlayerCPPAI::api;

namespace PlayerCPPAI
{
	namespace AI
	{
		

		public ref class PlayerAIBase
		{
		public:
			enum class STATUS
			{
				// Called ever N ticks to update the AI with the game status.
				UPDATE,
				// The car has no path.
				NO_PATH,
				// The passenger was abandoned, no passenger was picked up.
				PASSENGER_ABANDONED,
				// The passenger was delivered, no passenger was picked up.
				PASSENGER_DELIVERED,
				// The passenger was delivered or abandoned, a new passenger was picked up.
				PASSENGER_DELIVERED_AND_PICKED_UP,
				// The passenger refused to exit at the bus stop because an enemy was there.
				PASSENGER_REFUSED,
				// A passenger was picked up. There was no passenger to deliver.
				PASSENGER_PICKED_UP,
				// At a bus stop, nothing happened (no drop off, no pick up).
				PASSENGER_NO_ACTION
			};

			delegate void PlayerOrdersEvent(String ^order, List<Point> ^path, List<Passenger^> ^pickUp);
		};

		public interface class IPlayerAI
		{

			// Called when your robot must be placed on the board. This is called at the start of the game.
			// map: The game map.
			// me: My Player object. This is also in the players list.
			// players: All players (including you).
			// companies: The companies on the map.
			// passengers: The passengers that need a lift.
			// ordersEvent: Method to call to send orders to the server.
			void Setup(Map^, Player^, List<Player^>^, List<Company^>^, List<Passenger^>^, PlayerAIBase::PlayerOrdersEvent^);

			// Called to send an update message to this A.I. We do NOT have to reply to it.
			// status: The status message.
			// plyrStatus: The status of my player.
			// players: The status of all players.
			// passengers: The status of all passengers.
			void GameStatus(PlayerAIBase::STATUS, Player^, List<Player^>^, List<Passenger^>^);
		};
	}
}
