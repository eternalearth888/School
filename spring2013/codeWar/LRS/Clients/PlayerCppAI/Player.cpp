#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include "PlayerCppAIException.h"
#include "Player.h"

using std::copy;
using std::exception;
using std::max;
using std::strcmp;
using std::cout;
using std::endl;

namespace PlayerCSharpAI
{
	namespace api
	{
		Player::POWER_MODE Player::parsePowerMode(const string& value)
		{
			if (strcmp(value.c_str(), "UP") == 0)
				return UP;
			if (strcmp(value.c_str(), "ANNOUNCED") == 0)
				return ANNOUNCED;
			if (strcmp(value.c_str(), "DOWN") == 0)
				return DOWN;

			throw PlayerCppAIException("invalid power mode");
		}

		Player::Player(const xml_node& element)
		{
			m_guid = new string(element.attribute("guid").value());
			m_lives = element.attribute("lives").as_int();
			m_damage = element.attribute("damage").as_int();
			m_score = element.attribute("score").as_int();
			m_numLockedCards = element.child("cards").attribute("num-locked").as_int();
			m_powerMode = parsePowerMode(element.attribute("power-mode").value());
			m_archive = Point(element.attribute("archive-x").as_int(), element.attribute("archive-y").as_int());

			m_robot = new Robot(element.child("robot"));
			m_flagStates = FlagState::FromXML(element.child("flags"));
			xml_node ndCards = element.child("cards");
			m_cards = Card::FromXML(ndCards);
		}

		Player::Player(const Player& p)
		{
			m_guid = new string(p.m_guid->c_str());
			m_lives = p.m_lives;
			m_damage = p.m_damage;
			m_score = p.m_score;
			m_numLockedCards = p.m_numLockedCards;
			m_powerMode = p.m_powerMode;
			m_archive = p.m_archive;

			m_robot = new Robot(*p.m_robot);
			m_flagStates = new vector<FlagState>(*p.m_flagStates);
			m_cards = new vector<Card>(*p.m_cards);
		}

		Player::~Player()
		{
			delete m_guid;

			delete m_robot;
			delete m_flagStates;
			delete m_cards;
		}

		vector<Player>* Player::FromXML(const xml_node& element)
		{
			vector<Player>* v = new vector<Player>;
			for (xml_node p = element.child("player"); p; p = p.next_sibling("player"))
				v->push_back(Player(p));
			return v;
		}

		string* Player::getGuid()
		{
			return m_guid;
		}

		void Player::setGuid(string* value)
		{
			m_guid = value;
		}

		vector<Card>* Player::getCards()
		{
			return m_cards;
		}

		void Player::setCards(vector<Card>* value)
		{
			m_cards = value;
		}

		int Player::getLives()
		{
			return m_lives;
		}

		void Player::setLives(int value)
		{
			m_lives = value;
		}

		int Player::getDamage()
		{
			return m_damage;
		}

		void Player::setDamage(int value)
		{
			m_damage = value;
		}

		Point Player::getArchive()
		{
			return m_archive;
		}

		void Player::setArchive(Point value)
		{
			m_archive = value;
		}

		PlayerCSharpAI::api::Robot* Player::getRobot()
		{
			return m_robot;
		}

		void Player::setRobot(Robot* value)
		{
			m_robot = value;
		}

		PlayerCSharpAI::api::Player::POWER_MODE Player::getPowerMode()
		{
			return m_powerMode;
		}

		void Player::setPowerMode(POWER_MODE value)
		{
			m_powerMode = value;
		}

		int Player::getScore()
		{
			return m_score;
		}

		bool Player::getIsVisible()
		{
			return getMode() != DEAD && getMode() != DESTROYED;
		}

		PlayerCSharpAI::api::Player::MODE Player::getMode()
		{
			if (m_lives <= 0)
				return DEAD;
			if (m_damage >= 10)
				return DESTROYED;
			if (m_powerMode == DOWN)
				return POWER_DOWN;
			return ACTIVE;
		}

		int Player::getNumLockedCards()
		{
			return m_numLockedCards;
		}

		vector<FlagState>* Player::getFlagStates()
		{
			return m_flagStates;
		}

		void Player::setFlagStates(vector<FlagState>* value)
		{
			m_flagStates = value;
		}

		Player& Player::operator=(const Player& p)
		{
			delete m_guid;

			delete m_robot;
			delete m_flagStates;
			delete m_cards;

			m_guid = new string(p.m_guid->c_str());
			m_lives = p.m_lives;
			m_damage = p.m_damage;
			m_powerMode = p.m_powerMode;
			m_archive = p.m_archive;

			m_robot = new Robot(*p.m_robot);
			m_flagStates = new vector<FlagState>(*p.m_flagStates);
			m_cards = new vector<Card>(*p.m_cards);

			return *this;
		}
	}
}
