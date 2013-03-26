#ifndef MY_PLAYER_BRAIN_H
#define MY_PLAYER_BRAIN_H

#include <string>
#include <vector>
#include "BoardLocation.h"
#include "Card.h"
#include "GameMap.h"
#include "Image.h"
#include "Player.h"
#include "PlayerTurn.h"
#include "Point.h"
#include "Utilities.h"

using std::string;
using std::vector;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{
	/// The sample C++ AI. Start with this project but write your own code as this is a very simplistic implementation of the AI.
	class MyPlayerBrain
	{
	public:
		MyPlayerBrain(char* name, char* password);

		/// The name of the player.
		string getName();

		string getPassword();

		/// The avatar of the player. Must be 32 x 32.
		Image* getAvatar();

		// Called when your robot must be placed on the board. This is called at the start of the game and each time your robot dies.
		// Caller is responsible for deleting the pointer.
		// map: The game map. There will be no units on this map.
		// you: Your player object.
		// players: All players (including you).
		// robotStart: The position(s) on the map where you can place your robot. This will be a single point unless another robot is on your archive point.
		// gameStart: true if start of a game. false if re-entering the game.
		// returns: Where to place your unit (location and direction).
		BoardLocation* Setup(GameMap& map, Player& you, vector<Player>& players, vector<Point>& robotStart, bool gameStart);

		// Called each time the system needs another turn. If you do not return a valid turn, the game will randomly move one of your units.
		// This call must return in under 1 second. If it has not returned in 1 second the call will be aborted and a random move will be assigned.
		// Caller is responsible for deleting the pointer.
		// map: The game map with all units on it.
		// you: Your player object. This is created for each call.
		// allPlayers: All players including you. This is created for each call.
		// cards: The cards you get to pick from. This does not include locked cards.
		// returns: Your requested turn.
		PlayerTurn* Turn(GameMap& map, Player& you, vector<Player>& allPlayers, vector<Card>& cards);

	private:
		static const int NUM_CARDS = 1;
		string m_name;
		string m_password;
	};
}

#endif