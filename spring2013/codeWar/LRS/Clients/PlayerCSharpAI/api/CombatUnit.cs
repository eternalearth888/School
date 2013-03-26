// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// Any unit that fires (Robot and Laser) inherits from this class.
	/// </summary>
	public abstract class CombatUnit
	{
		/// <summary>
		/// Create from passed in XML..
		/// </summary>
		/// <param name="element">Initialize with the values in this object.</param>
		protected CombatUnit(XElement element)
		{
			Location = new BoardLocation(element);
		}

		/// <summary>
		/// The location on the map for this unit. Ignored if the unit is dead.
		/// </summary>
		public BoardLocation Location { get; set; }
	}
}
