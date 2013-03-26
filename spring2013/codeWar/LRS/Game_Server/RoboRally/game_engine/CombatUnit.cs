
using System.Collections.Generic;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// Any unit that fires (Robot and Laser) inherits from this class.
	/// </summary>
	public abstract class CombatUnit
	{
		/// <summary>
		/// Create the object.
		/// </summary>
		/// <param name="location">The unit is at this location on the map.</param>
		protected CombatUnit(BoardLocation location)
		{
			Location = location;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		protected CombatUnit(CombatUnit src)
		{
			Location = src.Location;
		}

		/// <summary>
		/// The location on the map for this unit. Ignored if the unit is dead.
		/// </summary>
		public BoardLocation Location { get; set; }

		public List<XAttribute> Attributes
		{
			get { return Location.Attributes; }
		}
	}
}
