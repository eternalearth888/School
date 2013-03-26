#include "FlagState.h"

namespace PlayerCSharpAI
{
	namespace api
	{

		FlagState::FlagState(const xml_node& element)
		{
			m_pos = Point(element.attribute("x").as_int(), element.attribute("y").as_int());
			m_touched = element.attribute("touched").as_bool();
		}

		vector<FlagState>* FlagState::FromXML(const xml_node& element)
		{
			vector<FlagState>* v = new vector<FlagState>;
			for (xml_node ndFlgSt = element.child("flag-state"); ndFlgSt; ndFlgSt = ndFlgSt.next_sibling("flag-state"))
				v->push_back(FlagState(ndFlgSt));
			return v;
		}

		Point FlagState::getPosition() const
		{
			return m_pos;
		}

		void FlagState::setPosition(Point value)
		{
			m_pos = value;
		}

		bool FlagState::getTouched() const
		{
			return m_touched;
		}

		void FlagState::setTouched(bool value)
		{
			m_touched = value;
		}
	}
}
