#ifndef COMBAT_UNIT_H
#define COMBAT_UNIT_H

#include "BoardLocation.h"
#include "pugixml.hpp"

using pugi::xml_node;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// Any unit that fires (Robot and Laser) inherits from this class.
		class CombatUnit
		{
		public:
			CombatUnit(const CombatUnit& c);
			~CombatUnit();

			// caller must not delete pointer.
			BoardLocation* getLocation() const;
			void setLocation(BoardLocation* value);

			CombatUnit& operator=(const CombatUnit& c);

		protected:
			CombatUnit();
			/// Create from passed in XML..
			/// element: Initialize with the values in this object.
			CombatUnit(const xml_node& element);

		private:
			/// The location on the map for this unit. Ignored if the unit is dead.
			BoardLocation* m_location;
		};
	}
}

#endif