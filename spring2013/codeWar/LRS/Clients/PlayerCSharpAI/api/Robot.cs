// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// A player's robot.
	/// </summary>
	public class Robot : CombatUnit
	{
		/// <summary>
		/// Build from XML.
		/// </summary>
		/// <param name="elemOn">Initialize with the values in this object.</param>
		public Robot(XElement elemOn) : base(elemOn)
		{
		}
	}
}
