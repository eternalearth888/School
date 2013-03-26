#include "Robot.h"

namespace PlayerCSharpAI
{
	namespace api
	{
		Robot::Robot() : CombatUnit()
		{

		}

		Robot::Robot(const xml_node& elemOn) : CombatUnit(elemOn)
		{

		}

		Robot::Robot(const Robot& r) : CombatUnit(r)
		{

		}

		Robot& Robot::operator=(const Robot& r)
		{
			CombatUnit::operator=(r);
			return *this;
		}
	}
}
