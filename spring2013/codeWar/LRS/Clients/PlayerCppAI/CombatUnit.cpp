#include "CombatUnit.h"

namespace PlayerCSharpAI
{
	namespace api
	{

		PlayerCSharpAI::api::BoardLocation* CombatUnit::getLocation() const
		{
			return m_location;
		}

		void CombatUnit::setLocation(BoardLocation* value)
		{
			m_location = value;
		}

		CombatUnit::CombatUnit() : m_location(NULL)
		{

		}

		CombatUnit::CombatUnit(const xml_node& element)
		{
			m_location = new BoardLocation(element);
		}

		CombatUnit::CombatUnit(const CombatUnit& c)
		{
			m_location = new BoardLocation(*c.m_location);
		}

		CombatUnit::~CombatUnit()
		{
			delete m_location;
		}

		CombatUnit& CombatUnit::operator=(const CombatUnit& c)
		{
			m_location = new BoardLocation(*c.m_location);
			return *this;
		}
	}
}
