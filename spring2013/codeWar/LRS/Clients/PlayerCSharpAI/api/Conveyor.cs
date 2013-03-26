// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// A converyor belt. This is an element of a map square and represents the conveyor belt on that single square.
	/// </summary>
	public class Conveyor
	{

		/// <summary>
		/// Build from XML serialization of this object.
		/// </summary>
		/// <param name="element">Initialize with the values in this object.</param>
		public Conveyor(XElement element)
		{
			Speed = int.Parse(element.Attribute("speed").Value);
			Direction = (MapSquare.DIRECTION)Enum.Parse(typeof(MapSquare.DIRECTION), element.Attribute("direction").Value);
			Entry = (MapSquare.SIDE)Enum.Parse(typeof(MapSquare.SIDE), element.Attribute("entry").Value);
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
	}
}
