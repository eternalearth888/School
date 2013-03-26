#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include "FlagState.h"
#include "Point.h"
#include "pugixml.hpp"
#include "Robot.h"

using pugi::xml_node;
using std::string;
using std::vector;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A player in the game. No Listmembers because we have to be visible to J#.
		class Player
		{
		public:
			/// What mode the player/robot is in.
			enum MODE
			{
				/// Standard mode - it is moving around the board.
				ACTIVE,
				/// It is powered down - static on the board.
				POWER_DOWN,
				/// It is destroyed - will return next turn.
				DESTROYED,
				/// It is dead - lost all 3 life tokens.
				DEAD
			};

			/// The power down mode for this player.
			enum POWER_MODE
			{
				/// Running (not down, not announced).
				UP,
				/// Announced, will power down at the end of the turn.
				ANNOUNCED,
				/// Powered down.
				DOWN
			};

			static POWER_MODE parsePowerMode(const string& value);

			/// Create from the XML.
			/// element: Initialize with the values in this object.
			Player(const xml_node& element);
			Player(const Player& p);
			~Player();

			// Creates a list of players from the xml.
			// Caller is responsible for deleting pointer.
			static vector<Player>* FromXML(const xml_node& element);

			// caller must not delete the pointer.
			string* getGuid();
			void setGuid(string* value);
			
			// Gets the cards for this player. Caller must not delete the pointer.
			vector<Card>* getCards();
			void setCards(vector<Card>* value);
			
			int getLives();
			void setLives(int value);
			
			int getDamage();
			void setDamage(int value);
			
			Point getArchive();
			void setArchive(Point value);
			
			// Gets this player's robot. Caller must not delete the pointer.
			Robot* getRobot();
			void setRobot(Robot* value);
			
			POWER_MODE getPowerMode();
			void setPowerMode(POWER_MODE value);

			/// The score for this player.
			int getScore();

			/// true if the player's robot is visible (on the map). False if it is dead or destroyed.
			bool getIsVisible();

			/// The mode this player is in.
			MODE getMode();

			/// The number of the player's cards that are locked. Locked cards are the last N cards from the previous turn.
			int getNumLockedCards();

			// Gets the flag states. Caller must not delete the pointer.
			vector<FlagState>* getFlagStates();
			void setFlagStates(vector<FlagState>* value);

			Player& operator=(const Player& p);

		private:
			/// The unique identifier for this player. This will remain constant for the length of the game (while the Player objects passed will
			/// change on every call).
			string* m_guid;

			/// The Cards for this player.
			vector<Card>* m_cards;

			/// The number of lives this player has. Starts at 3 and when it is 0 the player is dead and removed from the board.
			int m_lives;
			
			/// The level of damage this player has. Starts at 0, cards start locking at 5, and the player dies (Lives decreases by
			/// one) when it hits 10.
			int m_damage;

			/// The location the players robot will re-enter on if it dies.
			Point m_archive;

			/// The player's robot.
			Robot* m_robot;

			/// The power down mode for the player.
			POWER_MODE m_powerMode;

			int m_score;

			int m_numLockedCards;

			/// Where the flags are and if they've been touched.
			vector<FlagState>* m_flagStates;
		};
	}
}

#endif