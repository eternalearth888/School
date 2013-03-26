// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// A player in the game. No Listmembers because we have to be visible to J#.
	/// </summary>
	public class Player 
	{

		/// <summary>
		/// What mode the player/robot is in.
		/// </summary>
		public enum MODE
		{
			/// <summary>
			/// Standard mode - it is moving around the board.
			/// </summary>
			ACTIVE,

			/// <summary>
			/// It is powered down - static on the board.
			/// </summary>
			POWER_DOWN,

			/// <summary>
			/// It is destroyed - will return next turn.
			/// </summary>
			DESTROYED,

			/// <summary>
			/// It is dead - lost all 3 life tokens.
			/// </summary>
			DEAD
		};

		/// <summary>
		/// The power down mode for this player.
		/// </summary>
		public enum POWER_MODE
		{
			/// <summary>
			/// Running (not down, not announced).
			/// </summary>
			UP,

			/// <summary>
			/// Announced, will power down at the end of the turn.
			/// </summary>
			ANNOUNCED,

			/// <summary>
			/// Powered down.
			/// </summary>
			DOWN
		};

		/// <summary>
		/// Create from the XML.
		/// </summary>
		/// <param name="element">Initialize with the values in this object.</param>
		public Player(XElement element)
		{
			Guid = element.Attribute("guid").Value;
			Lives = int.Parse(element.Attribute("lives").Value);
			Damage = int.Parse(element.Attribute("damage").Value);
			Score = int.Parse(element.Attribute("score").Value);
			NumLockedCards = int.Parse(element.Element("cards").Attribute("num-locked").Value);
			PowerMode = (POWER_MODE)Enum.Parse(typeof(POWER_MODE), element.Attribute("power-mode").Value);
			Archive = new Point(int.Parse(element.Attribute("archive-x").Value), int.Parse(element.Attribute("archive-y").Value));

			Robot = new Robot(element.Element("robot"));
			FlagStates = FlagState.FromXML(element.Element("flags"));
			Cards = Card.FromXML(element.Element("cards"));
		}

		public static List<Player> FromXML(XElement element)
		{
			return element.Elements("player").Select(elemOn => new Player(elemOn)).ToList();
		}

		/// <summary>
		/// The unique identifier for this player. This will remain constant for the length of the game (while the Player objects passed will
		/// change on every call).
		/// </summary>
		public string Guid { get; private set; }

		/// <summary>
		/// The Cards for this player.
		/// </summary>
		public List<Card> Cards { get; set; }

		/// <summary>
		/// The number of lives this player has. Starts at 3 and when it is 0 the player is dead and removed from the board.
		/// </summary>
		public int Lives { get; protected set; }

		/// <summary>
		/// The level of damage this player has. Starts at 0, cards start locking at 5, and the player dies (Lives decreases by
		/// one) when it hits 10.
		/// </summary>
		public int Damage { get; protected set; }

		/// <summary>
		/// The location the players robot will re-enter on if it dies.
		/// </summary>
		public Point Archive { get; protected set; }

		/// <summary>
		/// The player's robot.
		/// </summary>
		public Robot Robot { get; private set; }

		/// <summary>
		/// The power down mode for the player.
		/// </summary>
		public POWER_MODE PowerMode { get; protected set; }

		/// <summary>
		/// The score for this player.
		/// </summary>
		public int Score { get; private set; }

		/// <summary>
		/// true if the player's robot is visible (on the map). False if it is dead or destroyed.
		/// </summary>
		public bool IsVisible
		{
			get { return Mode != MODE.DEAD && Mode != MODE.DESTROYED; }
		}

		/// <summary>
		/// The mode this player is in.
		/// </summary>
		public MODE Mode
		{
			get
			{
				if (Lives <= 0)
					return MODE.DEAD;
				if (Damage >= 10)
					return MODE.DESTROYED;
				if (PowerMode == POWER_MODE.DOWN)
					return MODE.POWER_DOWN;
				return MODE.ACTIVE;
			}
		}

		/// <summary>
		/// The number of the player's cards that are locked. Locked cards are the last N cards from the previous turn.
		/// </summary>
		public int NumLockedCards { get; private set; }

		/// <summary>
		/// Where the flags are and if they've been touched.
		/// </summary>
		public List<FlagState> FlagStates { get; protected set; }
	}
}
