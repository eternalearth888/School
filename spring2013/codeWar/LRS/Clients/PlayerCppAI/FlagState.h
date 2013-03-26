#ifndef FLAG_STATE_H
#define FLAG_STATE_H

#include <vector>
#include "Point.h"
#include "pugixml.hpp"

using pugi::xml_node;
using std::vector;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// The state of the flags for a player.
		class FlagState
		{
		public:
			/// Build from XML.
			/// element: Initialize with the values in this object.
			FlagState(const xml_node& element);

			static vector<FlagState>* FromXML(const xml_node& element);
			
			Point getPosition() const;
			void setPosition(Point value);
			
			bool getTouched() const;
			void setTouched(bool value);

		private:
			/// Which square the flag is on.
			Point m_pos;
			/// true if the flag has been touched. Once all 3 flags are touched a player has won.
			bool m_touched;
		};
	}
}

#endif