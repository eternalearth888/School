// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// Adds engine items to the player object.
	/// </summary>
	public abstract class Player
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
		/// What the communication with the remote AI player mode is.
		/// </summary>
		public enum COMM_MODE
		{
			/// <summary>
			/// Player is ready - not waiting for anything from remote AI.
			/// </summary>
			READY,
			/// <summary>
			/// Waiting for location reply. Use for both setup and re-enter after destroyed.
			/// </summary>
			WAITING_FOR_LOCATION,
			/// <summary>
			/// Waiting for turn reply.
			/// </summary>
			WAITING_FOR_TURN,
		}

		/// <summary>
		/// Create a player object. This is used during setup.
		/// </summary>
		/// <param name="guid">The unique identifier for this player.</param>
		/// <param name="name">The name of the player.</param>
		/// <param name="password">The password of the player.</param>
		/// <param name="avatar">The avatar of the player. Must be 32 x 32.</param>
		/// <param name="archive">The archive square for this player.</param>
		/// <param name="robot">The robot for this player.</param>
		/// <param name="flags">The location of flags on the map. All will be marked not touched.</param>
		/// <param name="spriteColor">The color of this player's sprite.</param>
		protected Player(string guid, string name, string password, Image avatar, Point archive, Robot robot, IEnumerable<Point> flags, Color spriteColor)
		{
			Guid = guid;
			Name = name;
			Password = password;
			Avatar = avatar;
			Archive = archive;
			Robot = robot;
			FlagStates = new List<FlagState>();
			foreach (Point flagOn in flags)
				FlagStates.Add(new FlagState(flagOn));
			SpriteColor = spriteColor;

			ServerAllowedArchive = new List<Point>();
			ServerDealtCards = new List<Card>();
			Score = 0;
			Scoreboard = new List<int>();

			Reset();
		}

		/// <summary>
		/// A shallow copy constructor. Used when re-ordering players.
		/// </summary>
		/// <param name="src">The source layer.</param>
		/// <param name="archive">The archive square for this player.</param>
		/// <param name="robot">The robot for this player.</param>
		/// <param name="spriteColor">The color of this player's sprite.</param>
		protected Player(Player src, Point archive, Robot robot, Color spriteColor)
		{
			Guid = src.Guid;
			TcpGuid = src.TcpGuid;
			Password = src.Password;
			Name = src.Name;
			Avatar = src.Avatar;
			Cards = src.Cards;
			Lives = src.Lives;
			Damage = src.Damage;
			Archive = src.Archive;
			PowerMode = src.PowerMode;
			FlagStates = new List<FlagState>(src.FlagStates);

			ServerAllowedArchive = src.ServerAllowedArchive;
			ServerDealtCards = src.ServerDealtCards;
			Score = src.Score;
			Scoreboard = new List<int>(src.Scoreboard);

			Archive = archive;
			Robot = robot;
			SpriteColor = spriteColor;
		}

		public void Reset()
		{
			Cards = new List<Card>();
			Lives = 3;
			Damage = 0;
			Score = 0;
			PowerMode = POWER_MODE.UP;

			foreach (FlagState flagOn in FlagStates)
				flagOn.Touched = false;

			WaitingForReply = COMM_MODE.READY;
			ServerAllowedArchive.Clear();
			ServerDealtCards.Clear();
		}

		#region properties

		/// <summary>
		/// The unique identifier for this player. This will remain constant for the length of the game (while the Player objects passed will
		/// change on every call).
		/// </summary>
		public string Guid { get; private set; }

		/// <summary>
		/// The GUID for this player's connection. This will change if the connection has to be re-established.
		/// </summary>
		public string TcpGuid { get; set; }

		/// <summary>
		/// The password of the player.
		/// </summary>
		public string Password { get; private set; }

		/// <summary>
		/// The name of the player.
		/// </summary>
		public string Name { get; private set; }

		/// <summary>
		/// The avatar of the player. Must be 32 x 32.
		/// </summary>
		public Image Avatar { get; private set; }

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
		/// We are waiting for a reply from this player.
		/// </summary>
		public COMM_MODE WaitingForReply { get; set; }

		/// <summary>
		/// The score for this player - this game
		/// </summary>
		public int Score { get; set; }

		/// <summary>
		/// The score for this player - previous games.
		/// </summary>
		public List<int> Scoreboard { get; private set; }

		/// <summary>
		/// The number of flags the player has touched. 
		/// </summary>
		public int FlagsTouched
		{
			get { return FlagStates.Count(fs => fs.Touched); }
		}

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
		public int NumLockedCards
		{
			get { return Math.Min(Math.Max(Damage - (9 - Framework.NUM_PHASES), 0), Framework.NUM_PHASES); }
		}

		/// <summary>
		/// Where the flags are and if they've been touched.
		/// </summary>
		public List<FlagState> FlagStates { get; protected set; }

		/// <summary>
		/// The color for this player on the status window.
		/// </summary>
		public Color SpriteColor { get; private set; }

		/// <summary>
		/// The player object as passed to the client AIs.
		/// </summary>
		public XElement XML
		{
			get
			{
				XElement xmlPlayer = new XElement("player", new XAttribute("guid", Guid), new XAttribute("lives", Lives),
												new XAttribute("damage", Damage), new XAttribute("power-mode", PowerMode),
												new XAttribute("score", Score), 
												new XAttribute("archive-x", Archive.X), new XAttribute("archive-y", Archive.Y));
				xmlPlayer.Add(Robot.XML);
				XElement xmlFlags = new XElement("flags");
				foreach (FlagState flagOn in FlagStates)
					xmlFlags.Add(flagOn.XML);
				xmlPlayer.Add(xmlFlags);
				XElement xmlCards = new XElement("cards", new XAttribute("num-locked", NumLockedCards));
				foreach (Card cardOn in Cards)
					xmlCards.Add(cardOn.XML);
				xmlPlayer.Add(xmlCards);
				return xmlPlayer;
			}
		}

		#endregion

		#region data sent to the client (to verify that the returned vales are valid)

		/// <summary>
		/// Points this player can enter on. This was sent to client
		/// </summary>
		public List<Point> ServerAllowedArchive { get; set; }

		/// <summary>
		/// The cards dealt to a player. This was sent to the client.
		/// </summary>
		public List<Card> ServerDealtCards { get; set; }

		#endregion

		/// <summary>
		/// Decrease lives by 1. If decreased to 0, mark player destroyed.
		/// </summary>
		public void DecreaseLives()
		{
			Lives--;
			Damage = 10; // mark as destroyed till next turn
			Robot.Location = new BoardLocation(new Point(-1, -1), Robot.Location.Direction);

			// if it was powered down, bring it back up.
			PowerMode = POWER_MODE.UP;

			if (Mode == MODE.DEAD)
				Cards = new List<Card>();
		}

		/// <summary>
		/// Player touched the flag at this location.
		/// </summary>
		/// <param name="position">The map square touched.</param>
		public void TouchedFlag(Point position)
		{
			Archive = position;
			// has to be the next one
			foreach (FlagState flagOn in FlagStates)
			{
				if (flagOn.Position == position)
				{
					if (! flagOn.Touched)
						Score += 5;
					flagOn.Touched = true;
					break;
				}
				if (!flagOn.Touched)
					break;
			}
		}

		/// <summary>
		/// Repair (decrease Damage by 1) for this player. Set as new Archive position for player.
		/// </summary>
		/// <param name="position">The map location repaired at.</param>
		public void Repair(Point position)
		{
			Archive = position;
			Damage = Math.Max(0, Damage - 1);
		}

		/// <summary>
		/// Set the new Archive position for the player.
		/// </summary>
		/// <param name="position">The map location for the new archive position.</param>
		public void SetArchive(Point position)
		{
			Archive = position;
		}

		/// <summary>
		/// Increase damage by 1. If increased to 10, mark dead.
		/// </summary>
		public void IncreaseDamage()
		{
			Damage++;
			if (Damage < 10) 
				return;

			Robot.Location = new BoardLocation(new Point(-1, -1), MapSquare.DIRECTION.NORTH);
			DecreaseLives();
		}

		/// <summary>
		/// Reset damage back to 0.
		/// </summary>
		public void UnDestroy()
		{
			Damage = 0;
			PowerMode = POWER_MODE.UP;
		}

		/// <summary>
		/// Power down this player.
		/// </summary>
		public void PowerDown()
		{
			PowerMode = POWER_MODE.DOWN;
			Damage = 0;
			PowerDownTurnsRemaining = 5 / Framework.NUM_PHASES;
		}

		/// <summary>
		/// Power up this player.
		/// </summary>
		public void PowerUp()
		{
			PowerMode = POWER_MODE.UP;
		}

		/// <summary>
		/// How many turns remain in power down mode.
		/// </summary>
		public int PowerDownTurnsRemaining { get; set; }

		/// <summary>
		/// Announce power down for this player. Will power down at the end of the turn on.
		/// </summary>
		public void AnnouncePowerMode()
		{
			PowerMode = POWER_MODE.ANNOUNCED;
		}
	}
}
