
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A laser on the board. This sits on a specific map square.
	/// </summary>
	public class Laser : CombatUnit
	{
		/// <summary>
		/// Create a new laser object.
		/// </summary>
		/// <param name="location">The unit is at this location on the map.</param>
		/// <param name="numSquares">The number of squares the laser shoots over, including the one it is on. (The Laser is ended by a wall.)</param>
		public Laser(BoardLocation location, int numSquares) : base(location)
		{
			NumSquares = numSquares;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public Laser(Laser src) : base(src)
		{
			NumSquares = src.NumSquares;
		}

		/// <summary>
		/// The number of squares the laser shoots over, including the one it is on. (The Laser is ended by a wall.)
		/// </summary>
		public int NumSquares { get; private set; }

		public XElement XML
		{
			get
			{
				XElement element = new XElement("laser", new XAttribute("num-squares", NumSquares));
				element.Add(Attributes);
				return element;
			}
		}
	}
}
