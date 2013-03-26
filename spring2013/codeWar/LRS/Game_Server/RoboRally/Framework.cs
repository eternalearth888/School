// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using RoboRallyNet.game_ai;
using RoboRallyNet.game_engine;
using System.Windows.Forms;

namespace RoboRallyNet
{
	/// <summary>
	/// This is the layer between the XML messages and the engine. It also handles the basic game timer.
	/// </summary>
	public class Framework : IEngineCallback
	{

		/// <summary>
		/// The state the game is presently in for communications with the players.
		/// </summary>
		public enum COMM_STATE
		{
			/// <summary>
			/// Accepting players joining the game.
			/// </summary>
			ACCEPTING_JOINS,

			/// <summary>
			/// Waiting for players to send setup info.
			/// </summary>
			ACCEPTING_SETUP,

			/// <summary>
			/// Players all setup, ready to start the game.
			/// </summary>
			READY_TO_START,

			/// <summary>
			/// Waiting for players to send in a turn.
			/// </summary>
			ACCEPTING_TURN,
			
			/// <summary>
			/// Processing a turn (or otherwise not sending/waiting on any communication).
			/// </summary>
			PROCESSING_TURN,

			/// <summary>
			/// For killed players, waiting for new start location.
			/// </summary>
			ACCEPTING_REENTRY,

			/// <summary>
			/// The game is paused.
			/// </summary>
			PAUSED,

			/// <summary>
			/// Game is over.
			/// </summary>
			GAME_OVER,
		}

		private COMM_STATE commState = COMM_STATE.ACCEPTING_JOINS;

		// how many turns until end of the game
		private const int NUM_TURNS = 60;

		// how many milliseconds allowed for each turn.
#if DEBUG_MODE
		private int milliTurnTimeLimit = 1000000;
#else
		private int milliTurnTimeLimit = 6000; // local uses 2000, national uses 6000
#endif

		// how many phases in a turn
		internal const int NUM_PHASES = 1;

		// how many times we update sprites per second
		private const int FRAMES_PER_SECOND = 24; // playoff uses 24
		// how many of the above frames before we move a unit/do next turn.
		private int framesPerMove = 6;	// playoff starts with 6 (4 moves/second)

		// the number of frame ticks from the start of the game.
		internal int frameTicks;
		// the number of frame ticks to occur until the next move tick.
		private int ticksTillMove;

		internal readonly TcpServer tcpServer = new TcpServer();

		// allowed passwords
		private readonly List<string> allowedPasswords = new List<string>();

		// new connections
		private readonly List<string> pendingGuids = new List<string>();

		// the explosion sprites.
		internal readonly List<Sprite> sprites = new List<Sprite>();
		// the laser beams firing.
		internal readonly List<LaserBeam> laserBeams = new List<LaserBeam>();

		// the game engine
		private readonly Engine engine;

		// the main window.
		internal readonly IUserDisplay mainWindow;

		// The game timer. Fires on every animation tick.
		private Timer timerWorker;

		// The communication timer. Fires 1 second after requesting a turn.
		private Timer timerClientWait;

		private static readonly Random rand = new Random();

		// true when we'll accept messages
		bool acceptMessages = true;

		/// <summary>
		/// Create the engine.
		/// </summary>
		/// <param name="mainWindow">The main window.</param>
		public Framework(IUserDisplay mainWindow)
		{
			this.mainWindow = mainWindow;
			engine = new Engine(this);

			GetPasswords();

			tcpServer.Start(this);
		}

		// get the allowed players
		private void GetPasswords()
		{
			allowedPasswords.Clear();
			ConfigurationManager.RefreshSection("RoboRallyNet");
			NameValueCollection coll = (NameValueCollection) ConfigurationManager.GetSection("RoboRallyNet");
			string[] passwords = coll["players"].Split(new[] {','}, StringSplitOptions.RemoveEmptyEntries);
			allowedPasswords.AddRange(passwords);
		}

		public Engine GameEngine
		{
			get { return engine; }
		}

		public int MovesPerSecond
		{
			get { return FRAMES_PER_SECOND / framesPerMove; }
			set { framesPerMove = FRAMES_PER_SECOND / value; }
		}

		public int TurnTimeoutSeconds
		{
			get { return milliTurnTimeLimit/1000; }
			set { milliTurnTimeLimit = value*1000; }
		}

		private delegate void StatusMessageDelegate(string text);
		private delegate void IncomingMessageDelegate(string guid, string message);

		public void StatusMessage(string message)
		{
			mainWindow.CtrlForInvoke.BeginInvoke(new StatusMessageDelegate(mainWindow.StatusMessage), new object[] { message });
		}

		public void ConnectionEstablished(string guid)
		{
			pendingGuids.Add(guid);
		}

		public void IncomingMessage(string guid, string message)
		{
			mainWindow.CtrlForInvoke.BeginInvoke(new IncomingMessageDelegate(_IncomingMessage), new object[] { guid, message });
		}

		public void ConnectionLost(string guid)
		{
			mainWindow.CtrlForInvoke.BeginInvoke(new StatusMessageDelegate(_ConnectionLost), new object[] { guid });
		}

		private void _ConnectionLost(string guid)
		{
			Player player = engine.Players.Where(pl => pl.TcpGuid == guid).FirstOrDefault();
			if (player == null)
			{
				Trace.WriteLine(string.Format("WARN: unknown TCP GUID {0} dropped", guid));
				return;
			}
			player.TcpGuid = null;

			// if waiting for this player only, now ready to process the turn
			bool isWaitingDroppedOnly;
			lock (this)
			{
				bool otherWaiting = engine.Players.Any(pl => pl != player && pl.WaitingForReply != Player.COMM_MODE.READY);
				isWaitingDroppedOnly = (player.WaitingForReply != Player.COMM_MODE.READY) && !otherWaiting;
				player.WaitingForReply = Player.COMM_MODE.READY;
			}
			if (isWaitingDroppedOnly)
				CommTimeout(null, null);

			string msg = string.Format("Player {0} lost connection", player.Name);
			Trace.WriteLine("INFO: " + msg);
			mainWindow.StatusMessage(msg);
		}

		/// <summary>
		/// The game play mode.
		/// </summary>
		public COMM_STATE Mode
		{
			get { return commState; }
		}

		private void _IncomingMessage(string guid, string message)
		{

			if (! acceptMessages)
			{
				Trap.trap();
				return;
			}

			try
			{
				// get the xml
				XDocument xml;
				try
				{
					xml = XDocument.Parse(message);
				}
				catch (Exception ex)
				{
					Trace.WriteLine(string.Format("ERROR: bad message (XML) from connection {0}, exception: {1}", guid, ex));
					// if an existing player we'll just ignore it. Otherwise we close the connection
					if (engine.Players.Any(pl => pl.TcpGuid == guid))
						return;
					Trap.trap();
					tcpServer.CloseConnection(guid);
					return;
				}

				Player player = engine.Players.Where(pl => pl.TcpGuid == guid).FirstOrDefault();
				XElement root = xml.Root;
				if (root == null)
				{
					Trap.trap();
					Trace.WriteLine(string.Format("ERROR: bad message (XML) from connection {0} - no root node", guid));
					return;
				}

				// if not an existing player, it must be <join>
				if ((player == null) && (root.Name.LocalName != "join"))
				{
					Trace.WriteLine(string.Format("ERROR: new player from connection {0} - not a join", guid));
					tcpServer.CloseConnection(guid);
					return;
				}

				switch (root.Name.LocalName)
				{
					case "join":
						MsgPlayerJoining(player, guid, root);
						return;
					case "start-position" :
						MsgPlayerStartPosition(player, guid, root);
						return;
					case "turn" :
						MsgPlayerTurn(player, guid, root);
						return;
					default:
						Trap.trap();
						Trace.WriteLine(string.Format("ERROR: bad message (XML) from server - root node {0}", root.Name.LocalName));
						break;
				}
			}
			catch (Exception ex)
			{
				Trap.trap();
				mainWindow.StatusMessage(string.Format("Error on incoming message. Exception: {0}", ex));
			}
		}

		private void CommTimerStart()
		{
			lock (this)
			{
				CommTimerClose();
				timerClientWait = new Timer {Interval = milliTurnTimeLimit};
				timerClientWait.Tick += CommTimeout;
				timerClientWait.Start();
			}
		}

		private void CommTimerClose()
		{
			lock (this)
			{
				if (timerClientWait == null) 
					return;
				timerClientWait.Stop();
				timerClientWait.Dispose();
				timerClientWait = null;
			}
		}

		private void CommTimeout(object sender, EventArgs e)
		{
			CommTimerClose();
			switch (commState)
			{
				case COMM_STATE.ACCEPTING_SETUP:
					Play();
					break;
				case COMM_STATE.ACCEPTING_REENTRY:
					engine.ExecuteStartTurn();
					break;
				default: // should be COMM_STATE.ACCEPTING_TURN
					Trap.trap(commState != COMM_STATE.ACCEPTING_TURN);
					engine.TurnStartTimout();
					break;
			}
		}

		/// <summary>
		/// Player is (re)joining the game.
		/// </summary>
		/// <param name="player">The player. null if a join, non-null (maybe) if a re-join.</param>
		/// <param name="guid">The tcp guid of the message.</param>
		/// <param name="root">The XML message.</param>
		private void MsgPlayerJoining(Player player, string guid, XElement root)
		{

			// if the player exists do nothing because we're already set up (client sent it twice).
			if (player != null)
			{
				Trap.trap();
				Trace.WriteLine(string.Format("ERROR: join on existing connected player. connection: {0}", guid));
				return;
			}
			// must have a name and password
			string name = AttributeOrNull(root, "name");
			string password = AttributeOrNull(root, "password");
			if (string.IsNullOrEmpty(name) || string.IsNullOrEmpty(password))
			{
				Trap.trap();
				Trace.WriteLine(string.Format("ERROR: join with no name and/or password refused. Name: {0}", name));
				tcpServer.CloseConnection(guid);
				return;
			}
			// check for new connection on existing player
			player = engine.Players.Where(pl => pl.Password == password).FirstOrDefault();
			if (player != null)
			{
				player.TcpGuid = guid;
				Trace.WriteLine(string.Format("INFO: Player {0} reconnected", name));
				mainWindow.StatusMessage(string.Format("Player {0} reconnected", name));

				Trap.trap(player.WaitingForReply != Player.COMM_MODE.READY);
				player.WaitingForReply = Player.COMM_MODE.READY;
				if (commState == COMM_STATE.ACCEPTING_REENTRY || commState == COMM_STATE.ACCEPTING_SETUP || commState == COMM_STATE.ACCEPTING_TURN)
					engine.CheckAllTurnsIn();
				return;
			}

			// allowed password?
			if (!allowedPasswords.Contains(password))
			{
				Trace.WriteLine(string.Format("ERROR: join with illegal password refused. Name: {0}", name));
				mainWindow.StatusMessage(string.Format("join with illegal password refused. Name: {0}", name));
				tcpServer.CloseConnection(guid);
				return;
			}

			// unique name?
			player = engine.Players.Where(pl => pl.Name == name).FirstOrDefault();
			if (player != null)
			{
				player.TcpGuid = guid;
				Trace.WriteLine(string.Format("ERROR: Player {0} name already exists, duplicate refused.", name));
				mainWindow.StatusMessage(string.Format("Player {0} name already exists, duplicate refused.", name));
				tcpServer.CloseConnection(guid);
				return;
			}

			int ind = engine.Players.Count;
			// should be impossible (because of allowedPasswords) but check
			if (ind >= 8)
			{
				Trace.WriteLine(string.Format("ERROR: can't add a 9th player. Name: {0}", name));
				tcpServer.CloseConnection(guid);
				return;
			}

			// we're in progress - no new players
			if (commState != COMM_STATE.ACCEPTING_JOINS)
			{
				Trace.WriteLine(string.Format("ERROR: game in progress - new players not allowed. Name: {0}", name));
				mainWindow.StatusMessage(string.Format("game in progress - new players not allowed. Name: {0}", name));
				tcpServer.CloseConnection(guid);
				return;
			}

			// ok, we're all good. Create the player
			XElement elemAvatar = root.Element("avatar");
			Image avatar = null;
			if (elemAvatar != null)
			{
				try
				{
					byte[] data = Convert.FromBase64String(elemAvatar.Value);
					avatar = new Bitmap(new MemoryStream(data));
					if ((avatar.Width != 32) || (avatar.Height != 32))
						mainWindow.StatusMessage(string.Format("Avatar for player {0} not 32x32", name));
				}
				catch (Exception ex)
				{
					mainWindow.StatusMessage(string.Format("Avatar for player {0} had error {1}", name, ex.Message));
				}
			}
			player = new PlayerAI(Guid.NewGuid().ToString(), name, password, avatar, startSquare[ind],
			                    new Robot(new BoardLocation(startSquare[ind], MapSquare.DIRECTION.NORTH), robotBitmaps[ind]),
			                    allFlags, playerColors[ind])
			         	{TcpGuid = guid};
			engine.Players.Add(player);

			// if we have 8, we're ready to go
			if (engine.Players.Count >= 8)
			{
				Trap.trap();
				CloseJoins();
			}

			string msg = string.Format("Player {0} joined from {1}", name, tcpServer.GetIpAddress(guid));
			Trace.WriteLine("INFO: " + msg);
			mainWindow.StatusMessage(msg);

			mainWindow.NewPlayerAdded();
			mainWindow.UpdateMenu();
		}

		/// <summary>
		/// Initialize the game, ask players for start positions.
		/// </summary>
		public void CloseJoins()
		{

			// add AI players as needed
			for (int ind = 0; engine.Players.Count < 8; ind++)
				engine.Players.Add(new PlayerAI(Guid.NewGuid().ToString(), simpleAiNames[ind], "ai", null, startSquare[ind],
				                                new Robot(new BoardLocation(startSquare[ind], MapSquare.DIRECTION.NORTH),
				                                          robotBitmaps[ind]), allFlags, playerColors[ind]));
			InitializeGame();
		}

		private void InitializeGame() {

			commState = COMM_STATE.ACCEPTING_SETUP;

#if DEBUG_MODE
			// leave AI we're testing as player 0
			List<Player> reorderedPlayers = new List<Player>(engine.Players);
#else
			// change the order
			List<Player> reorderedPlayers = engine.Players.OrderBy(pl => rand.Next()).ToList();
#endif
			engine.Players.Clear();
			for (int ind = 0; ind < reorderedPlayers.Count; ind++)
			{
				Player srcPlayer = reorderedPlayers[ind];
				Player destPlayer = new PlayerAI(srcPlayer, startSquare[ind], new Robot(new BoardLocation(startSquare[ind], MapSquare.DIRECTION.NORTH), robotBitmaps[ind]), playerColors[ind]);
				engine.Players.Add(destPlayer);
			}

			// reset engine & players
			engine.Initialize();
			
			// ask each player for their start location.
			foreach (Player plyr in engine.Players)
				RequestStartPosition(plyr, new List<Point> {plyr.Archive}, true);

			CommTimerStart();

			mainWindow.SetupGame();
			mainWindow.UpdateMenu();
		}

		public void RestartJoins()
		{
			acceptMessages = false;

			GetPasswords();

			foreach (Player plyr in engine.Players)
				tcpServer.CloseConnection(plyr.TcpGuid);
			engine.Players.Clear();

			commState = COMM_STATE.ACCEPTING_JOINS;
			acceptMessages = true;

			const string msg = "Clear players, re-open for joins";
			Trace.WriteLine("INFO: " + msg);
			mainWindow.StatusMessage(msg);

			mainWindow.ResetPlayers();
			mainWindow.UpdateMenu();
		}

		/// <summary>
		/// Ask the player to provide the start or re-entry position.
		/// </summary>
		/// <param name="plyr">The player to ask.</param>
		/// <param name="allowedPoints">The list of allowed positions.</param>
		/// <param name="gameStart">true if the game is starting. false if coming back on the board after dying.</param>
		public void RequestStartPosition(Player plyr, List<Point> allowedPoints, bool gameStart)
		{

			if (plyr.TcpGuid == null)
			{
				plyr.Robot.Location = ((PlayerAI)plyr).Setup(allowedPoints);
				plyr.WaitingForReply = Player.COMM_MODE.READY;
				return;
			}

			XDocument doc = new XDocument();
			XElement root = new XElement("start-position", new XAttribute("game-start", gameStart));

			// allowed starting points
			XElement positions = new XElement("points");
			foreach (Point pt in allowedPoints)
				positions.Add(new XElement("position", new XAttribute("x", pt.X), new XAttribute("y", pt.Y)));
			root.Add(positions);

			// game map
			root.Add(engine.MainMap.XML);

			// all players
			XElement allPlayers = new XElement("players", new XAttribute("your-guid", plyr.Guid));
			foreach (Player plyrOn in engine.Players)
				allPlayers.Add(plyrOn.XML);
			root.Add(allPlayers);

			// set this so when we get the message, we know what's allowed.
			plyr.ServerAllowedArchive = allowedPoints;
			plyr.WaitingForReply = Player.COMM_MODE.WAITING_FOR_LOCATION;

			doc.Add(root);
			tcpServer.SendMessage(plyr.TcpGuid, doc.ToString());
		}

		/// <summary>
		/// Engine is now waiting for reentry positions to come in.
		/// </summary>
		public void WaitingForReentry()
		{
			lock (this)
			{
				if (!engine.Players.Any(pl => pl.WaitingForReply != Player.COMM_MODE.READY))
				{
					Trap.trap();
					commState = COMM_STATE.PROCESSING_TURN;
					mainWindow.UpdateMenu();
					return;
				}
				commState = COMM_STATE.ACCEPTING_REENTRY;
				mainWindow.UpdateMenu();
				CommTimerStart();
			}
		}

		/// <summary>
		/// Player is setting a start or re-entry position.
		/// </summary>
		/// <param name="player">The player.</param>
		/// <param name="tcpGuid">The tcp guid of the message.</param>
		/// <param name="root">The XML message.</param>
		private void MsgPlayerStartPosition(Player player, string tcpGuid, XElement root)
		{

			BoardLocation location;
			try
			{
				int x = int.Parse(root.Attribute("x").Value);
				int y = int.Parse(root.Attribute("y").Value);
				MapSquare.DIRECTION dir = (MapSquare.DIRECTION) Enum.Parse(typeof(MapSquare.DIRECTION), root.Attribute("direction").Value);
				Point pt = new Point(x, y);
				Trap.trap(! player.ServerAllowedArchive.Contains(pt));
				location = player.ServerAllowedArchive.Contains(pt) ? new BoardLocation(pt, dir) : new BoardLocation(player.ServerAllowedArchive[0], MapSquare.DIRECTION.NORTH);
				Trace.WriteLine(string.Format("Player {0} provided a start location of {1}", player.Name, location));
			}
			catch (Exception ex)
			{
				Trap.trap();
				Trace.WriteLine("ERROR: start-position threw error " + ex.Message);
				location = new BoardLocation(player.ServerAllowedArchive[0], MapSquare.DIRECTION.NORTH);
				Trace.WriteLine(string.Format("Player {0} assigned a start location of {1}", player.Name, location));
			}

			engine.PlayerSetArchive(player, location);

			// if all done - ready to start
			if (!engine.Players.Any(pl => pl.Robot.Location.IsNull && pl.TcpGuid != null))
			{
				CommTimerClose();
				foreach (Player plyrOn in engine.Players)
					plyrOn.WaitingForReply = Player.COMM_MODE.READY;
				if (commState == COMM_STATE.ACCEPTING_SETUP)
					commState = COMM_STATE.READY_TO_START;
				else if (commState == COMM_STATE.ACCEPTING_REENTRY)
					commState = COMM_STATE.PROCESSING_TURN;
				mainWindow.UpdateMenu();
			}
			else Trap.trap();
		}

		public void RequestTurn(GameMap map, Player player, List<Player> players, List<Card> cards)
		{

			if (player.TcpGuid == null)
			{
				PlayerTurn turn = ((PlayerAI)player).Turn(map, player, cards);
				engine.PlayerTurn(player, turn.Cards, turn.IsPowerDown);
				player.WaitingForReply = Player.COMM_MODE.READY;
				return;
			}
			
			// create the map and all players part of the xml
			XDocument doc = new XDocument();
			XElement xmlTurn = new XElement("turn", new XAttribute("turn", engine.TurnOn), new XAttribute("repair-on", engine.IsRepairTurn));

			xmlTurn.Add(map.XML);
			XElement xmlPlayers = new XElement("players", new XAttribute("your-guid", player.Guid));
			foreach (Player plyrOn in players)
				xmlPlayers.Add(plyrOn.XML);
			xmlTurn.Add(xmlPlayers);

			// and set this player guid and cards
			XElement xmlCards = new XElement("cards");
			foreach (Card card in cards)
				xmlCards.Add(card.XML);
			xmlTurn.Add(xmlCards);

			doc.Add(xmlTurn);

			// request the turn
			tcpServer.SendMessage(player.TcpGuid, doc.ToString());
		}

		/// <summary>
		/// Engine is now waiting for turns to come in.
		/// </summary>
		public void WaitingForTurns()
		{
			lock (this)
			{
				if (! engine.Players.Any(pl => pl.WaitingForReply != Player.COMM_MODE.READY))
				{
					commState = COMM_STATE.PROCESSING_TURN;
					mainWindow.UpdateMenu();
					return;
				}
				commState = COMM_STATE.ACCEPTING_TURN;
				mainWindow.UpdateMenu();
				CommTimerStart();
			}
		}

		/// <summary>
		/// Engine has received all turns.
		/// </summary>
		public void ReceivedAllTurns()
		{
			CommTimerClose();
			commState = COMM_STATE.PROCESSING_TURN;
			mainWindow.UpdateMenu();
		}

		/// <summary>
		/// Player is giving us their turn.
		/// </summary>
		/// <param name="player">The player.</param>
		/// <param name="tcpGuid">The tcp guid of the message.</param>
		/// <param name="root">The XML message.</param>
		private void MsgPlayerTurn(Player player, string tcpGuid, XElement root)
		{
			bool powerDown;
			List<Card> cards;
			try
			{
				// check for earlier turn coming in (after timeout)
				int turnOn = int.Parse(root.Attribute("turn").Value);
				if (turnOn != engine.TurnOn)
				{
					string msg = string.Format("ERROR: player {0} provided turn {1}, presently waiting for turn {2}", player.Name, turnOn, engine.TurnOn);
					Trace.WriteLine(msg);
					mainWindow.StatusMessage(msg);
					return;
				}

				XAttribute attr = root.Attribute("power-down");
				powerDown = attr != null && attr.Value.ToLower() == "true";
				cards = Card.FromXML(root);
			}
			catch (Exception ex)
			{
				Trap.trap();
				Trace.WriteLine(string.Format("ERROR: player {0} turn message threw error {1}", player.Name, ex.Message));
				powerDown = false;
				cards = new List<Card>(player.ServerDealtCards.Take(NUM_PHASES - player.NumLockedCards));
			}
			engine.PlayerTurn(player, cards, powerDown);
		}

		/// <summary>
		/// Start or continue (from pause) the game.
		/// </summary>
		public void Play()
		{
			engine.StepMode = false;
			_Play();
		}

		private void _Play()
		{
			
			// in case a reset
			if (timerWorker == null)
			{
				if (engine.GameOn != 0)
					InitializeGame();
				engine.GameOn++;

				frameTicks = ticksTillMove = 0;
				sprites.Clear();

				timerWorker = new Timer {Interval = 1000/FRAMES_PER_SECOND, Tag = rand.Next()};
				timerWorker.Tick += FrameTick;
			}

			if ((commState == COMM_STATE.ACCEPTING_JOINS) || (commState == COMM_STATE.ACCEPTING_SETUP))
				commState = COMM_STATE.READY_TO_START;
			mainWindow.UpdateMenu();

			timerWorker.Start();
		}

		public void Step()
		{
			engine.StepMode = true;
			sprites.Clear();
			laserBeams.Clear();
			_Play();
		}

		public void PauseAtEndOfTurn()
		{
			engine.StepMode = true;
		}

		/// <summary>
		/// Pause the game.
		/// </summary>
		public void Pause()
		{
			commState = COMM_STATE.PAUSED;
			CommTimerClose();
			timerWorker.Stop();

			// clear off explosions
			mainWindow.UpdateMap();
			mainWindow.UpdateMenu();
		}

		/// <summary>
		/// End the game.
		/// </summary>
		public void Stop()
		{
			commState = COMM_STATE.GAME_OVER;
			CommTimerClose();
			if (timerWorker != null)
			{
				timerWorker.Stop();
				timerWorker.Dispose();
				timerWorker = null;
			}
			commState = COMM_STATE.GAME_OVER;

			// clear off explosions
			sprites.Clear();
			laserBeams.Clear();
			mainWindow.UpdateMap();
			mainWindow.UpdateMenu();
		}

		/// <summary>
		/// The main timer tick handler. Calls all game logic from here on each tick.
		/// </summary>
		private void FrameTick(object sender, EventArgs e)
		{

			// update sprites. Some may be deleted. Update if any sprites
			bool updateSprites = sprites.Count > 0;
			List<Sprite> dead = sprites.Where(spriteOn => spriteOn.IncreaseTick()).ToList();
			foreach (Sprite spriteOn in dead)
				sprites.Remove(spriteOn);

			// if not time for a move, we're done. Update if any sprites changed.
			frameTicks++;
			ticksTillMove--;
			if (ticksTillMove > 0)
			{
				if (updateSprites)
					mainWindow.UpdateMap();
				return;
			}

			// find winner in case game over
			Player plyrWin = engine.Players.OrderByDescending(pl => pl.Score).First();

			// check for everyone dead
			int numPlayers = engine.Players.Count(pl => pl.Mode != Player.MODE.DEAD);
			if (numPlayers == 0)
			{
				mainWindow.StatusMessage(string.Format("All players are dead,  winner {0} with {1} points", plyrWin.Name, plyrWin.Score));
				GameOver();
				return;
			}

			// check for just 1 alive
			if (numPlayers == 1)
			{
				Player plyrLast = engine.Players.First(pl => pl.Mode != Player.MODE.DEAD);
				plyrLast.Score *= 2;
				plyrWin = engine.Players.OrderByDescending(pl => pl.Score).First();
				mainWindow.StatusMessage(string.Format("Player {0} last man standing, winner {1} with {2} points", plyrLast.Name, plyrWin.Name, plyrWin.Score));
				GameOver();
				return;
			}

			// turns up?
			if (engine.TurnOn > NUM_TURNS)
			{
				mainWindow.StatusMessage(string.Format("Game over, winner {0} with {1} points", plyrWin.Name, plyrWin.Score));
				GameOver();
				return;
			}

			engine.Tick();

			ticksTillMove = framesPerMove;
			mainWindow.UpdateMap();
		}

		private void GameOver()
		{
			Stop();
			// add scores to playes
			foreach (Player plyrOn in engine.Players)
				plyrOn.Scoreboard.Add(plyrOn.Score);
			mainWindow.UpdatePlayers();
			mainWindow.UpdateMenu();
			mainWindow.UpdateMap();
		}

		private static string AttributeOrNull(XElement element, string name)
		{
			XAttribute attr = element.Attribute(name);
			return attr == null ? null : attr.Value;
		}

		// names for SimpleAI
		private static readonly string[] simpleAiNames = {
		                                          	"Sheldon Cooper", "Leonard Hofstadter", "Rajesh Koothrappali", "Howard Wolowitz",
		                                          	"Penny", "Bernadette Rostenkowski", "Amy Farrah Fowler", "Leslie Winkle"
		                                          };
		
		private static readonly Point[] allFlags = { new Point(5, 4), new Point(10, 11), new Point(1, 6) };

		private static readonly Point[] startSquare = {
		                                              	new Point(5, 15), new Point(6, 15), new Point(3, 14), new Point(8, 14),
		                                              	new Point(1, 13), new Point(10, 13), new Point(0, 12),
		                                              	new Point(11, 12)
		                                              };

#if DEBUG_MODE
		private static readonly Bitmap[] robotBitmaps = {
		                                                	Sprites.bot_debug, Sprites.bot_1, Sprites.bot_2, Sprites.bot_3,
		                                                	Sprites.bot_4, Sprites.bot_5, Sprites.bot_6, Sprites.bot_7
		                                                };
#else
		private static readonly Bitmap[] robotBitmaps = {
		                                                	Sprites.bot_0, Sprites.bot_1, Sprites.bot_2, Sprites.bot_3,
		                                                	Sprites.bot_4, Sprites.bot_5, Sprites.bot_6, Sprites.bot_7
		                                                };
#endif

		private static readonly Color[] playerColors = {
		                                               	Color.DarkKhaki, Color.DarkGreen, Color.Crimson, Color.Magenta,
		                                               	Color.DarkGray, Color.Orange, Color.CornflowerBlue, Color.DeepPink
		                                               };

	}
}
