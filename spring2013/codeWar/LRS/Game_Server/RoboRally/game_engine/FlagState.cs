// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Drawing;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// The state of the flags for a player.
	/// </summary>
	public class FlagState
	{
		/// <summary>
		/// Create the object. Flag is set to not touched.
		/// </summary>
		/// <param name="position">Which square the flag is on.</param>
		public FlagState(Point position)
		{
			Position = position;
			Touched = false;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public FlagState(FlagState src)
		{
			Position = src.Position;
			Touched = src.Touched;
		}

		/// <summary>
		/// Which square the flag is on.
		/// </summary>
		public Point Position { get; protected set; }

		/// <summary>
		/// true if the flag has been touched. Once all 3 flags are touched a player has won.
		/// </summary>
		public bool Touched { get; set; }

		public XElement XML
		{
			get
			{
				return new XElement("flag-state", new XAttribute("x", Position.X), new XAttribute("y", Position.Y), new XAttribute("touched", Touched));
			}
		}
	}
}