#include <cstdlib>
#include <cstring>
#include <sstream>
#include "PlayerCppAIException.h"
#include "Card.h"

using std::atoi;
using std::exception;
using std::strcmp;

namespace PlayerCSharpAI
{
	namespace api
	{
		Card::ROBOT_MOVE Card::parseRobotMove(const string& value)
		{
			if (strcmp(value.c_str(), "BACKWARD_ONE") == 0)
				return BACKWARD_ONE;
			if (strcmp(value.c_str(), "FORWARD_ONE") == 0)
				return FORWARD_ONE;
			if (strcmp(value.c_str(), "FORWARD_TWO") == 0)
				return FORWARD_TWO;
			if (strcmp(value.c_str(), "FORWARD_THREE") == 0)
				return FORWARD_THREE;
			if (strcmp(value.c_str(), "ROTATE_LEFT") == 0)
				return ROTATE_LEFT;
			if (strcmp(value.c_str(), "ROTATE_RIGHT") == 0)
				return ROTATE_RIGHT;
			if (strcmp(value.c_str(), "ROTATE_UTURN") == 0)
				return ROTATE_UTURN;
			
			throw PlayerCppAIException("invalid robot move");
		}

		string Card::strRobotMove(ROBOT_MOVE m)
		{
			switch (m)
			{
			case BACKWARD_ONE:
				return "BACKWARD_ONE";
			case FORWARD_ONE:
				return "FORWARD_ONE";
			case FORWARD_TWO:
				return "FORWARD_TWO";
			case FORWARD_THREE:
				return "FORWARD_THREE";
			case ROTATE_LEFT:
				return "ROTATE_LEFT";
			case ROTATE_RIGHT:
				return "ROTATE_RIGHT";
			case ROTATE_UTURN:
				return "ROTATE_UTURN";
			default:
				throw PlayerCppAIException("invalid robot move");
			}
		}

		Card::Card()
		{
			
		}

		Card::Card(ROBOT_MOVE move, int priority)
		{
			m_move = move;
			m_priority = priority;
		}

		Card::Card(const xml_node& element)
		{
			m_move = parseRobotMove(element.attribute("move").value());
			m_priority = atoi(element.attribute("priority").value());
		}

		vector<Card>* Card::FromXML(xml_node& element)
		{
			vector<Card>* v = new vector<Card>;
			for (xml_node ndCard = element.child("card"); ndCard; ndCard = ndCard.next_sibling("card"))
				v->push_back(Card(ndCard));
			return v;
		}

		Card::ROBOT_MOVE Card::getMove() const
		{
			return m_move;
		}

		void Card::setMove(ROBOT_MOVE value)
		{
			m_move = value;
		}

		int Card::getPriority() const
		{
			return m_priority;
		}

		void Card::setPriority(int value)
		{
			m_priority = value;
		}

		bool Card::isRotate() const
		{
			return m_move == ROTATE_LEFT || m_move == ROTATE_RIGHT || m_move == ROTATE_UTURN;
		}

		void Card::makeXML(xml_node& parent)
		{
			xml_node elem = parent.append_child("card");
			elem.append_attribute("priority").set_value(getPriority());
			elem.append_attribute("move").set_value(strRobotMove(getMove()).c_str());
		}

		string Card::toStr() const
		{
			std::stringstream out;
			out << getMove() << ":" << getPriority();
			return out.str();
		}
	}
}
