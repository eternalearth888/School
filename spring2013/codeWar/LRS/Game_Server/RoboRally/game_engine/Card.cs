
using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A card (move) for a robot.
	/// </summary>
	public struct Card
	{
		/// <summary>
		/// The move for this card.
		/// </summary>
		public enum ROBOT_MOVE
		{
			/// <summary>
			/// Backup one square.
			/// </summary>
			BACKWARD_ONE = 0,
			/// <summary>
			/// Forward one square.
			/// </summary>
			FORWARD_ONE = 1,
			/// <summary>
			/// Forward two squares.
			/// </summary>
			FORWARD_TWO = 2,
			/// <summary>
			/// Forward three squares.
			/// </summary>
			FORWARD_THREE = 3,
			/// <summary>
			/// Rotate left (counterclockwise) 1/4 of a circle. Stay on the same square.
			/// </summary>
			ROTATE_LEFT = 4,
			/// <summary>
			/// Rotate right (clockwise) 1/4 of a circle. Stay on the same square.
			/// </summary>
			ROTATE_RIGHT = 5,
			/// <summary>
			/// Rotate to the flip direction. Stay on the same square.
			/// </summary>
			ROTATE_UTURN = 6,
		}

		private ROBOT_MOVE move;
		private int priority;

		/// <summary>
		/// Create a Card object.
		/// </summary>
		/// <param name="move">The move for the card.</param>
		/// <param name="priority">The priority for the move. Higher priorities go first.</param>
		public Card(ROBOT_MOVE move, int priority) 
		{
			this.move = move;
			this.priority = priority;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public Card(Card src)
		{
			move = src.Move;
			priority = src.Priority;
		}

		public Card(XElement element)
		{
			priority = int.Parse(element.Attribute("priority").Value);
			move = (ROBOT_MOVE)Enum.Parse(typeof(ROBOT_MOVE), element.Attribute("move").Value);
		}

		/// <summary>
		/// The move for the card.
		/// </summary>
		public ROBOT_MOVE Move
		{
			get { return move; }
			set { move = value; }
		}

		/// <summary>
		/// The priority for the move. Higher priorities go first.
		/// </summary>
		public int Priority
		{
			get { return priority; }
			set { priority = value; }
		}

		/// <summary>
		/// true if this move is a rotation.
		/// </summary>
		public bool IsRotate
		{
			get { return (move == ROBOT_MOVE.ROTATE_LEFT) || (move == ROBOT_MOVE.ROTATE_RIGHT) || (move == ROBOT_MOVE.ROTATE_UTURN); }
		}
		
		public XElement XML
		{
			get
			{
				return new XElement("card", new XAttribute("move", Move), new XAttribute("priority", Priority));
			}
		}

		public static List<Card> FromXML (XElement element)
		{
			return element.Element("cards").Elements("card").Select(elemOn => new Card(elemOn)).ToList();
		}

		/// <summary>
		/// Displays the value of the object.
		/// </summary>
		/// <returns>The value of the object.</returns>
		public override string ToString()
		{
			return string.Format("{0} : {1}", Move, Priority);
		}
	};
}
