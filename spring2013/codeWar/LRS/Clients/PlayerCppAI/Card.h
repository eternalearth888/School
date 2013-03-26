#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include "pugixml.hpp"

using pugi::xml_node;
using pugi::xml_attribute;
using std::string;
using std::vector;

namespace PlayerCSharpAI
{
	namespace api
	{
		/// A card (move) for a robot.
		class Card
		{
		public:
			/// The move for this card.
			enum ROBOT_MOVE
			{
				/// Backup one square.
				BACKWARD_ONE = 0,
				/// Forward one square.
				FORWARD_ONE = 1,
				/// Forward two squares.
				FORWARD_TWO = 2,
				/// Forward three squares.
				FORWARD_THREE = 3,
				/// Rotate left (counterclockwise) 1/4 of a circle. Stay on the same square.
				ROTATE_LEFT = 4,
				/// Rotate right (clockwise) 1/4 of a circle. Stay on the same square.
				ROTATE_RIGHT = 5,
				/// Rotate to the flip direction. Stay on the same square.
				ROTATE_UTURN = 6,
			};

			static ROBOT_MOVE parseRobotMove(const string& value);
			static string strRobotMove(ROBOT_MOVE m);
			
			Card();
			Card(ROBOT_MOVE move, int priority);
			/// Build from XML.
			/// element: Initialize with the values in this object.
			Card(const xml_node& element);

			// Creates a list of cards from xml.
			// Caller is responsible for deleting the pointer.
			static vector<Card>* FromXML(xml_node& element);

			/// The move for the card.
			ROBOT_MOVE getMove() const;
			void setMove(ROBOT_MOVE value);

			/// The priority for the move. Higher priorities go first.
			int getPriority() const;
			void setPriority(int value);

			bool isRotate() const;

			/// Create the XML of the turn. put in parent.
			void makeXML(xml_node& parent);

			/// Displays the value of the object.
			string toStr() const;

		private:
			ROBOT_MOVE m_move;
			int m_priority;
		};
	}
}

#endif