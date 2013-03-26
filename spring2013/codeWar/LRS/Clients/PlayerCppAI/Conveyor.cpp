#include <cstdlib>
#include "Conveyor.h"

namespace PlayerCSharpAI
{
	namespace api
	{

		Conveyor::Conveyor(const xml_node& element)
		{
			m_speed = atoi(element.attribute("speed").value());
			m_direction = MapSquareProperty::parseDirection(element.attribute("direction").value());
			m_entry = MapSquareProperty::parseSide(element.attribute("entry").value())->at(0);
		}

		int Conveyor::getSpeed() const
		{
			return m_speed;
		}

		void Conveyor::setSpeed(int value)
		{
			m_speed = value;
		}

		MapSquareProperty::DIRECTION Conveyor::getDirection() const
		{
			return m_direction;
		}

		void Conveyor::setDirection(MapSquareProperty::DIRECTION value)
		{
			m_direction = value;
		}

		MapSquareProperty::SIDE Conveyor::getEntry() const
		{
			return m_entry;
		}

		void Conveyor::setEntry(MapSquareProperty::SIDE value)
		{
			m_entry = value;
		}
	}
}
