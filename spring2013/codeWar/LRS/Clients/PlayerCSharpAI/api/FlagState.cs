using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// The state of the flags for a player.
	/// </summary>
	public class FlagState
	{
		/// <summary>
		/// Build from XML.
		/// </summary>
		/// <param name="element">Initialize with the values in this object.</param>
		public FlagState(XElement element)
		{
			Position = new Point(int.Parse(element.Attribute("x").Value), int.Parse(element.Attribute("y").Value));
			Touched = element.Attribute("touched").Value.ToLower() == "true";
		}

		public static List<FlagState> FromXML(XElement element)
		{
			return element.Elements("flag-state").Select(flag => new FlagState(flag)).ToList();
		}

		/// <summary>
		/// Which square the flag is on.
		/// </summary>
		public Point Position { get; protected set; }

		/// <summary>
		/// true if the flag has been touched. Once all 3 flags are touched a player has won.
		/// </summary>
		public bool Touched { get; set; }
	}
}