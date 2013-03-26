#ifndef PLAYER_TURN_H
#define PLAYER_TURN_H

#include <string>
#include <vector>
#include "Card.h"
#include "pugixml.hpp"

using pugi::xml_node;
using std::string;
using std::vector;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{
	/// A requested move for a player's turn.
	class PlayerTurn
	{
	public:
		/// Return your turn. If you have locked cards will only use the first N (unlocked) cards returned. If you do not return 
		/// enough cards, random cards will be assigned. Locked cards are the last N cards from the previous turn.
		/// cards: Your unlocked cards.
		/// powerDown: true if power down at the end of this turn.
		PlayerTurn(vector<Card>* cards, bool powerDown);
		PlayerTurn(const PlayerTurn& p);
		~PlayerTurn();
		
		// caller must not delete the pointer.
		vector<Card>* getCards();
		void setCards(vector<Card>* value);
		
		bool getIsPowerDown();
		void setIsPowerDown(bool value);

		/// Create the XML of the turn.
		void makeXML(xml_node& parent);

		/// User friendly display.
		/// <returns>User friendly display.</returns>
		string toStr();

		PlayerTurn& operator=(const PlayerTurn& p);

	private:
		/// The cards requested for the upcoming turn. If your Damage is greater than 4 then not all 5 of these will be used, but you
		/// may return 5. The extras will be ignored.
		vector<Card>* m_cards;

		/// Return true to power down at the end of the upcoming turn. You also need to return Cards because the power down occurs
		/// AFTER this turn!
		bool m_isPowerDown;
	};
}

#endif