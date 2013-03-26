#pragma once

#include "Limo.h"
#include "Passenger.h"
#include "Util.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Xml;

namespace PlayerCPPAI
{
	namespace api
	{
		public ref class Player
		{
		private:
			Player(XmlElement ^elemPlayer);

		public:
			// The unique identifier for this player. This will remain constant for the length of the game (while the Player objects passed will
			// change on every call).
			property String ^Guid;

			// The name of the player.
			property String ^Name;

			// Who to pick up at the next bus stop. Can be empty and can also only list people not there.
			// This may be wrong after a pick-up occurs as all we get is a count. This is updated with the
			// most recent list sent to the server.
			property List<Passenger^> ^PickUp;

			// The passengers delivered - this game.
			property List<Passenger^> ^PassengersDelivered;

			// The player's limo.
			property Limo ^Limo;

			// The score for this player (this game, not across all games so far).
			property float Score;

			// Called on setup to create initial list of players.
			// elemPlayers: The xml with all the players.
			// returns: The created list of players.
			static List<Player^> ^FromXml(XmlElement ^elemPlayers);

			static void UpdateFromXml(List<Player^> ^players, List<Passenger^> ^passengers, XmlElement ^elemPlayers);

			virtual String ^ToString() override;
		};
	}
}
