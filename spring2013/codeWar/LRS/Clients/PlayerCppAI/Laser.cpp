#include "Laser.h"

namespace PlayerCSharpAI
{
	namespace api
	{
		Laser::Laser() : CombatUnit()
		{

		}

		Laser::Laser(const xml_node& element) : CombatUnit(element)
		{
			m_numSquares = element.attribute("num-squares").as_int();
		}

		Laser::Laser(const Laser& l) : CombatUnit(l)
		{
			m_numSquares = l.m_numSquares;
		}

		int Laser::getNumSquares() const
		{
			return m_numSquares;
		}

		Laser& Laser::operator=(const Laser& l)
		{
			CombatUnit::operator=(l);
			m_numSquares = l.m_numSquares;
			return *this;
		}

		/*void Laser::setNumSquares(int value)
		{
			m_numSquares = value;
		}*/
	}
}
