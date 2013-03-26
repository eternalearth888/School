// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// A laser on the board. This sits on a specific map square.
	/// </summary>
	public class Laser : CombatUnit
	{

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="element">Initialize with the values in this XML.</param>
		public Laser(XElement element)
			: base(element)
		{
			NumSquares = int.Parse(element.Attribute("num-squares").Value);
		}

		/// <summary>
		/// The number of squares the laser shoots over, including the one it is on. (The Laser is ended by a wall.)
		/// </summary>
		public int NumSquares { get; private set; }
	}
}
