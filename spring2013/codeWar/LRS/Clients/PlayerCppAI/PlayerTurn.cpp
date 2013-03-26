#include <cstring>
#include <sstream>
#include "PlayerTurn.h"

using namespace PlayerCSharpAI::api;
namespace PlayerCSharpAI
{

	PlayerTurn::PlayerTurn(vector<Card>* cards, bool powerDown)
	{
		m_cards = cards != NULL && cards->size() > 0 ? cards : new vector<Card>;
		m_isPowerDown = powerDown;
	}

	PlayerTurn::PlayerTurn(const PlayerTurn& p)
	{
		m_cards = new vector<Card>(*p.m_cards);
		m_isPowerDown = p.m_isPowerDown;
	}

	PlayerTurn::~PlayerTurn() 
	{
		delete m_cards;
	}

	vector<Card>* PlayerTurn::getCards()
	{
		return m_cards;
	}

	void PlayerTurn::setCards(vector<Card>* value)
	{
		m_cards = value;
	}

	bool PlayerTurn::getIsPowerDown()
	{
		return m_isPowerDown;
	}

	void PlayerTurn::setIsPowerDown(bool value)
	{
		m_isPowerDown = value;
	}

	void PlayerTurn::makeXML(xml_node& parent)
	{
		xml_node xmlTurn = parent.append_child("turn");
		xmlTurn.append_attribute("power-down").set_value(m_isPowerDown ? "true" : "false");
		xml_node xmlCards = xmlTurn.append_child("cards");
		for (vector<Card>::iterator cardOn = m_cards->begin(); cardOn != m_cards->end(); ++cardOn)
			cardOn->makeXML(xmlCards);
	}

	string PlayerTurn::toStr()
	{
		string s("Turn: Cards[");
		for (vector<Card>::iterator cardOn = m_cards->begin(); cardOn != m_cards->end(); ++cardOn)
		{
			s.append(cardOn->toStr());
			s.append(", ");
		}
		if (m_cards->size() > 0)
			s.erase(s.size() - 2, 2);
		s.append("]");
		if (m_isPowerDown)
			s.append(" PowerDown");
		return s;
	}

	PlayerTurn& PlayerTurn::operator=(const PlayerTurn& p)
	{
		delete m_cards;

		if (p.m_cards != NULL)
			m_cards = new vector<Card>(*p.m_cards);
		else
			m_cards = new vector<Card>;
		m_isPowerDown = p.m_isPowerDown;

		return *this;
	}
}
