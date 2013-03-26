
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A converyor belt. This is an element of a map square and represents the conveyor belt on that single square.
	/// </summary>
	public class Conveyor
	{
		/// <summary>
		/// Create the object.
		/// </summary>
		/// <param name="speed">The speed of the belt. Values are 1 or 2.</param>
		/// <param name="direction">The direction the belt exits at.</param>
		/// <param name="entry">The direction(s) the converyor belt enters from.</param>
		public Conveyor(int speed, MapSquare.DIRECTION direction, MapSquare.SIDE entry)
		{
			Speed = speed;
			Direction = direction;
			Entry = entry;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public Conveyor(Conveyor src)
		{
			Speed = src.Speed;
			Direction = src.Direction;
			Entry = src.Entry;
		}

		/// <summary>
		/// The speed of the belt. Values are 1 or 2.
		/// </summary>
		public int Speed { get; protected set; }

		/// <summary>
		/// The direction the belt exits at.
		/// </summary>
		public MapSquare.DIRECTION Direction { get; protected set; }

		/// <summary>
		/// The direction(s) the converyor belt enters from.
		/// </summary>
		public MapSquare.SIDE Entry { get; protected set; }

		public XElement XML
		{
			get
			{
				return new XElement("conveyor", new XAttribute("speed", Speed), new XAttribute("direction", Direction),
				                    new XAttribute("entry", Entry));
			}
		}
	}
}
