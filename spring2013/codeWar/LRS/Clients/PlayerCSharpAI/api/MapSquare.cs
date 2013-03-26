// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// An individual square in the map.
	/// </summary>
	public class MapSquare 
	{

		/// <summary>
		/// The direction a robot or laser is facing. ALso used for direction a conveyor is running (exit for a turn).
		/// </summary>
		public enum DIRECTION
		{
			/// <summary>
			/// Facing North and can fire on units above.
			/// </summary>
			NORTH = 0,
			/// <summary>
			/// Facing East and can fire on units to the right.
			/// </summary>
			EAST = 1,
			/// <summary>
			/// Facing South and can fire on units below.
			/// </summary>
			SOUTH = 2,
			/// <summary>
			/// Facing West and can fire on units to the left.
			/// </summary>
			WEST = 3
		};

		/// <summary>
		/// Which side(s) of the square have a wall. A square can have multiple walls.
		/// </summary>
		[Flags]
		public enum SIDE
		{
			/// <summary>
			/// No walls.
			/// </summary>
			NONE = 0,
			/// <summary>
			/// A wall on the North (top) side.
			/// </summary>
			NORTH = 0x01,
			/// <summary>
			/// A wall on the East (right) side.
			/// </summary>
			EAST = 0x02,
			/// <summary>
			/// A wall on the South (bottom) side.
			/// </summary>
			SOUTH = 0x04,
			/// <summary>
			/// A wall on the West (left) side.
			/// </summary>
			WEST = 0x08
		}

		/// <summary>
		/// What type of square it is.
		/// </summary>
		public enum TYPE
		{
			/// <summary>
			/// Normal - nothing on it.
			/// </summary>
			NORMAL,
			/// <summary>
			/// Has a conveyor belt on it.
			/// </summary>
			CONVEYOR_BELT,
			/// <summary>
			/// Is a gear that rotates clockwise.
			/// </summary>
			ROTATE_CLOCKWISE,
			/// <summary>
			/// Is a gear that rotates counter-clockwise.
			/// </summary>
			ROTATE_COUNTERCLOCKWISE,
			/// <summary>
			/// Is a repair square.
			/// </summary>
			REPAIR,
			/// <summary>
			/// Is a flag.
			/// </summary>
			FLAG,
			/// <summary>
			/// Is a pit.
			/// </summary>
			PIT
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="element">Serialized XML of this object..</param>
		public MapSquare(XElement element)
		{
			Type = (TYPE)Enum.Parse(typeof(TYPE), element.Attribute("type").Value);
			Walls = (SIDE)Enum.Parse(typeof(SIDE), element.Attribute("walls").Value);
			Flag = int.Parse(element.Attribute("flag").Value);

			XElement elemConveyor = element.Element("conveyor");
			Conveyor = elemConveyor == null ? null : new Conveyor(elemConveyor);

			XElement elemLaser = element.Element("laser");
			Laser = elemLaser == null ? null : new Laser(elemLaser);
		}

		/// <summary>
		/// The type of square.
		/// </summary>
		public TYPE Type { get; protected set; }

		/// <summary>
		/// What sides (if any) have walls.
		/// </summary>
		public SIDE Walls { get; protected set; }

		/// <summary>
		/// The conveyor belt on this square. null if no conveyor.
		/// </summary>
		public Conveyor Conveyor { get; protected set; }

		/// <summary>
		/// The laser on this square. null if no laser.
		/// </summary>
		public Laser Laser { get; protected set; }

		/// <summary>
		/// The flag number (1..3) on this square. 0 if no flag.
		/// </summary>
		public int Flag { get; protected set; }
	}
}
