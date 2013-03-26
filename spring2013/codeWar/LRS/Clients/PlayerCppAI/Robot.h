#ifndef ROBOT_H
#define ROBOT_H

#include "CombatUnit.h"
#include "pugixml.hpp"

using pugi::xml_node;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A player's robot.
		class Robot : public CombatUnit
		{
		public:
			Robot();
			/// Build from XML.
			/// elemOn: Initialize with the values in this object.
			Robot(const xml_node& elemOn);
			Robot(const Robot& r);

			Robot& operator=(const Robot& r);
		};
	}
}

#endif