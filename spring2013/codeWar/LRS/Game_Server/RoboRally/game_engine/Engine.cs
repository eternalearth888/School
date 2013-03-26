// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Media;
using System.Reflection;
using System.Text;

namespace RoboRallyNet.game_engine
{
	public class Engine 
	{
		/// <summary>
		/// The turn phase.
		/// </summary>
		private enum PHASE
		{
			/// <summary>
			/// Get the player turn.
			/// </summary>
			GET_TURN,

			/// <summary>
			/// Waiting for turn from players
			/// </summary>
			WAITING_ON_PLAYERS,

			/// <summary>
			/// Move robots.
			/// </summary>
			MOVE_ROBOT,

			/// <summary>
			/// Board movement.
			/// </summary>
			MOVE_BOARD,

			/// <summary>
			/// Fire lasers.
			/// </summary>
			FIRE,

			/// <summary>
			/// Check for robots on flag and archive spots.
			/// </summary>
			FLAG_ARCHIVE,

			/// <summary>
			/// Waiting for re-entry location.
			/// </summary>
			WAITING_ON_ARCHIVE,
		}

		private readonly Framework framework;

		// the [card] to do on the next tick. Value is 0..4
		private int cardOn;
		// the phase on
		private PHASE phaseOn = PHASE.GET_TURN;

		/// <summary>
		/// true if in step mode.
		/// </summary>
		public bool StepMode { get; set; }

		// The game map.
		internal GameMap MainMap { get; private set; }

		// plays the explosion.
		private readonly SoundPlayer explosionPlayer;
		private readonly SoundPlayer laserPlayer;
		private readonly SoundPlayer pitPlayer;

		// anytime we need a random number.
		private static readonly Random rand = new Random();

		public Engine(Framework framework)
		{
			PlaySounds = true;
			GameOn = 0;
			Players = new List<Player>();

			this.framework = framework;

			using (Stream wavFile = Assembly.GetExecutingAssembly().GetManifestResourceStream("RoboRallyNet.Resources.Explosion.wav"))
			{
				explosionPlayer = new SoundPlayer(wavFile);
				explosionPlayer.Load();
			}
			using (Stream wavFile = Assembly.GetExecutingAssembly().GetManifestResourceStream("RoboRallyNet.Resources.laser_blue.wav"))
			{
				laserPlayer = new SoundPlayer(wavFile);
				laserPlayer.Load();
			}
			using (Stream wavFile = Assembly.GetExecutingAssembly().GetManifestResourceStream("RoboRallyNet.Resources.pit.wav"))
			{
				pitPlayer = new SoundPlayer(wavFile);
				pitPlayer.Load();
			}

			// create the map
			MainMap = GameMap.CreateMap();
		}

		/// <summary>
		/// All of the players.
		/// </summary>
		internal List<Player> Players { get; private set; }

		/// <summary>
		/// Which game we ar eplaying (zero based).
		/// </summary>
		public int GameOn { get; set; }

		/// <summary>
		/// The turn we are presently on.
		/// </summary>
		public int TurnOn { get; private set; }

		public bool PlaySounds { get; set; }

		/// <summary>
		/// True if this is a turn the repair squares are on (repairing).
		/// </summary>
		public bool IsRepairTurn
		{
			get { return TurnOn%5 == 0; }
		}

		public void Initialize()
		{
			cardOn = 0;
			TurnOn = 0;
			phaseOn = PHASE.GET_TURN;
			MainMap = GameMap.CreateMap();
			foreach (Player plyr in Players)
				plyr.Reset();
		}

		#region execute turn/phase

		public void Tick()
		{
			// ok, time to execute this phase.
			switch (phaseOn)
			{
				// if phase 0, start the turn.
				case PHASE.GET_TURN:
					TurnOn++;
					ExecuteStartTurn();
					framework.mainWindow.UpdatePlayers();
					break;

				case PHASE.MOVE_ROBOT:
					framework.mainWindow.TurnNumber(TurnOn, cardOn + 1);
					ExecuteMoveRobot();
					phaseOn = PHASE.MOVE_BOARD;
					break;

				case PHASE.MOVE_BOARD:
					ExecuteMoveBoard();
					phaseOn = PHASE.FIRE;
					break;

				case PHASE.FIRE:
					ExecuteFire();
					phaseOn = PHASE.FLAG_ARCHIVE;
					framework.mainWindow.UpdatePlayers();
					break;

				case PHASE.FLAG_ARCHIVE:
					ExecuteFlagAndArchive();
					if (! StepMode)
						framework.laserBeams.Clear();
					cardOn++;

					// if last phase, end the turn.
					if (cardOn >= Framework.NUM_PHASES)
					{
						ExecuteEndTurn();
						if (StepMode)
							framework.Pause();
					}
					else
						phaseOn = PHASE.MOVE_ROBOT;
					framework.mainWindow.UpdatePlayers();
					break;
			}
		}

		/// <summary>
		/// get the cards for all players
		/// </summary>
		public void ExecuteStartTurn()
		{

			// set to waiting phase
			foreach (Player player in Players)
				player.WaitingForReply = Player.COMM_MODE.WAITING_FOR_TURN;
			phaseOn = PHASE.WAITING_ON_PLAYERS;
			ValidateData();

#if DEBUG
			Trace.WriteLine(string.Format("starting turn {0}", TurnOn));
			foreach (Player player in Players)
				Trace.WriteLine(string.Format("     Player {0}, mode {1}, Lives {2}, Damage {3}, Mode {4}, Location {5}",
				                              player.Name, player.Mode, player.Lives, player.Damage, player.Mode,
				                              player.Robot.Location));
#endif

			// create 40 cards.
			// unique priorities across all
			// ROBOT_MOVE num of cards in enum order are 6, 18, 12, 6, 18, 18, 6
			List<int> priorityNums = CreatePriorityNumbers();
			List<Card> cards = new List<Card>();
			cards.AddRange(priorityNums.Take(6).Select(priority => new Card(Card.ROBOT_MOVE.BACKWARD_ONE, priority)));
			cards.AddRange(priorityNums.Skip(6).Take(18).Select(priority => new Card(Card.ROBOT_MOVE.FORWARD_ONE, priority)));
			cards.AddRange(priorityNums.Skip(6 + 18).Take(12).Select(priority => new Card(Card.ROBOT_MOVE.FORWARD_TWO, priority)));
			cards.AddRange(priorityNums.Skip(6 + 18 + 12).Take(6).Select(priority => new Card(Card.ROBOT_MOVE.FORWARD_THREE, priority)));
			cards.AddRange(priorityNums.Skip(6 + 18 + 12 + 6).Take(18).Select(priority => new Card(Card.ROBOT_MOVE.ROTATE_LEFT, priority)));
			cards.AddRange(priorityNums.Skip(6 + 18 + 12 + 6 + 18).Take(18).Select(priority => new Card(Card.ROBOT_MOVE.ROTATE_RIGHT, priority)));
			cards.AddRange(priorityNums.Skip(6 + 18 + 12 + 6 + 18 + 18).Take(6).Select(priority => new Card(Card.ROBOT_MOVE.ROTATE_UTURN, priority)));

			Trace.WriteLine("Turns:");
			foreach (Player player in Players)
			{
				if (player.Mode == Player.MODE.DEAD)
				{
					player.Cards = new List<Card>();
					player.WaitingForReply = Player.COMM_MODE.READY;
					continue;
				}
				// if powered down keep old cards
				if (player.Mode == Player.MODE.POWER_DOWN)
				{
					player.WaitingForReply = Player.COMM_MODE.READY;
					continue;
				}

				// grab the players dealt cards
				int numCards = 9 - player.Damage;
				List<Card> dealtCards = new List<Card>();
				while (numCards-- > 0)
				{
					int index = rand.Next(cards.Count);
					dealtCards.Add(cards[index]);
					cards.RemoveAt(index);
				}
				player.ServerDealtCards = dealtCards;
				framework.RequestTurn(MainMap, player, Players, dealtCards);
			}

			// start timer for 1 second
			ValidateData();
			framework.WaitingForTurns();
			if (!Players.Any(pl => pl.WaitingForReply != Player.COMM_MODE.READY))
				phaseOn = PHASE.MOVE_ROBOT;
		}

		/// <summary>
		/// We did not get some turns, force it.
		/// </summary>
		public void TurnStartTimout()
		{
			foreach (Player player in Players.Where(player => player.WaitingForReply != Player.COMM_MODE.READY))
			{
				framework.mainWindow.StatusMessage(string.Format("Player {0} did not provide a turn", player.Name));
				PlayerTurn(player, new List<Card>(), false);
			}
			phaseOn = PHASE.MOVE_ROBOT;
		}

		public void PlayerTurn(Player player, List<Card> cards, bool powerDown)
		{
			// bugbug - handle timeout, message of who timed out.
			ValidateData();

			// if they aren't on the map (didn't get start position), set it
			if (player.Robot.Location.IsNull)
			{
				player.Robot.Location = new BoardLocation(player.ServerAllowedArchive[0], MapSquare.DIRECTION.NORTH);
				Trace.WriteLine(string.Format("WARNING: Player {0} did not provide a start location. Using {1}", player.Name, player.Robot.Location));
			}
			
			// turn this into a validated set of cards. Add random if too few, set with priority, copy over locked.
			List<Card> playerCards = new List<Card>();
			int numLockedCards = player.NumLockedCards;

			// make sure they selected from the list we gave them
			List<Card> copyDealt = new List<Card>(player.ServerDealtCards);
			for (int ind = 0; ind < Framework.NUM_PHASES - numLockedCards; ind++)
			{
				if ((ind < cards.Count) && (copyDealt.Contains(cards[ind])))
					{
						playerCards.Add(cards[ind]);
						copyDealt.Remove(cards[ind]);
						continue;
					}
				Card moveOn = copyDealt[rand.Next(copyDealt.Count - 1)];
				playerCards.Add(moveOn);
				copyDealt.Remove(moveOn);
			}

			for (int ind = Framework.NUM_PHASES - numLockedCards; ind < Framework.NUM_PHASES; ind++)
				if (player.Cards.Count > ind)
					playerCards.Add(player.Cards[ind]);
				else Trap.trap(); // should never happen
			player.Cards = playerCards;

			if (powerDown)
				player.AnnouncePowerMode();

			StringBuilder buf = new StringBuilder();
			foreach (Card plyrCard in playerCards)
				buf.Append(string.Format("{0}, ", plyrCard));
			buf.Remove(buf.Length - 2, 2);
			Trace.WriteLine(string.Format("     turn - Player: {0}; Cards: {1}{2}", player.Name, buf, player.PowerMode != Player.POWER_MODE.ANNOUNCED ? "" : " - power down announced"));
			ValidateData();
			player.WaitingForReply = Player.COMM_MODE.READY;

			CheckAllTurnsIn();
		}

		// if all done - ready to start
		public void CheckAllTurnsIn()
		{
			if (Players.Any(pl => pl.WaitingForReply != Player.COMM_MODE.READY)) 
				return;
			framework.ReceivedAllTurns();
			phaseOn = PHASE.MOVE_ROBOT;
		}

		// 84 unique numbers for 10 to 990
		private List<int> CreatePriorityNumbers()
		{

			// get priorities for locked cards
			List<int> arrLocked = new List<int>();
			foreach (Player playerOn in Players)
			{
				int numLockedCards = Math.Min(0, Math.Max(playerOn.Damage - (9 - Framework.NUM_PHASES), 0));
				for (int ind = Framework.NUM_PHASES - numLockedCards; ind < playerOn.Cards.Count; ind++)
					arrLocked.Add(playerOn.Cards[ind].Priority);
			}

			List<int> arr = new List<int>();
			while (arr.Count < 84)
			{
				int num = rand.Next(1, 99)*10;
				if ((!arr.Contains(num)) && (!arrLocked.Contains(num)))
					arr.Add(num);
			}
			return arr;
		}

		// move the robots for 1 phase (card).
		private void ExecuteMoveRobot()
		{

			Trace.WriteLine(string.Format("Move card[{0}]", cardOn));
			List<Player> plyrMove =
				Players.Where(pl => pl.IsVisible && (pl.PowerMode != Player.POWER_MODE.DOWN) && (pl.Cards.Count > cardOn)).OrderBy(
					pl => pl.Cards[cardOn].Priority).Reverse().ToList();

			foreach (Player playerOn in plyrMove)
			{
				ValidateData();
				// a previous player may have killed this player by pushing it off the board
				if ((!playerOn.IsVisible) || (playerOn.Cards.Count <= cardOn))
					continue;

				Card card = playerOn.Cards[cardOn];
				Trace.WriteLine(string.Format("     move requested - Player: {0}; Card: {1}, from {2}", playerOn.Name,
				                              card, playerOn.Robot.Location));
				int steps = 0;
				switch (card.Move)
				{
					case Card.ROBOT_MOVE.BACKWARD_ONE:
						steps = -1;
						break;
					case Card.ROBOT_MOVE.FORWARD_ONE:
						steps = 1;
						break;
					case Card.ROBOT_MOVE.FORWARD_TWO:
						steps = 2;
						break;
					case Card.ROBOT_MOVE.FORWARD_THREE:
						steps = 3;
						break;
					case Card.ROBOT_MOVE.ROTATE_LEFT:
						playerOn.Robot.Location = playerOn.Robot.Location.Rotate(-1);
						break;
					case Card.ROBOT_MOVE.ROTATE_RIGHT:
						playerOn.Robot.Location = playerOn.Robot.Location.Rotate(1);
						break;
					case Card.ROBOT_MOVE.ROTATE_UTURN:
						playerOn.Robot.Location = playerOn.Robot.Location.Rotate(2);
						break;
				}

				if (steps == 0)
				{
					Trace.WriteLine(string.Format("     move complete - Player: {0}; Card: {1}, now {2}", playerOn.Name,
					                              card, playerOn.Robot.Location));
					ValidateData();
					continue;
				}

				// move pushing other robots if needed.
				BoardLocation start = playerOn.Robot.Location;
				MapSquare.DIRECTION dir = steps >= 0
				                          	? playerOn.Robot.Location.Direction
				                          	: playerOn.Robot.Location.Rotate(2).Direction;
				while (steps != 0)
				{
					if (MoveRobot(playerOn, dir, playerOn) != MOVE_RESULT.OK)
						break;

					steps = steps >= 0 ? steps - 1 : steps + 1;
				}
				Trace.WriteLine(string.Format("     move complete - Player: {0}; Card: {1}, from {2} to {3}",
				                              playerOn.Name, card, start, playerOn.Robot.Location));
				ValidateData();
			}
		}

		private enum MOVE_RESULT
		{
			OK,
			DEAD,
			STUCK
		}

		private MOVE_RESULT MoveRobot(Player playerOn, MapSquare.DIRECTION dir, Player origPlayer)
		{

			Utilities.MovePoint mp = Utilities.Move(MainMap, playerOn.Robot.Location.MapPosition, dir);
			// if dead, handle that
			if (mp.Dead)
			{
				playerOn.DecreaseLives();
				if (playerOn.Mode == Player.MODE.DEAD)
				{
					Trace.WriteLine(string.Format("Player {0} has been killed", playerOn.Name));
					framework.mainWindow.StatusMessage(string.Format("Player {0} has been killed", playerOn.Name));
				}
				else
					Trace.WriteLine(string.Format("destroyed - Player {0}, Lives {1}", playerOn.Name, playerOn.Lives));
				if (PlaySounds)
					pitPlayer.Play();
				return MOVE_RESULT.DEAD;
			}
			// if can't move we're done
			if (mp.Location.MapPosition == playerOn.Robot.Location.MapPosition)
				return MOVE_RESULT.STUCK;
			// if hitting a robot, can we move it?
			Player plyrMoveRobot =
				Players.Where(pl => (pl.IsVisible) && (pl.Robot.Location.MapPosition == mp.Location.MapPosition)).FirstOrDefault();
			if (plyrMoveRobot != null)
			{
				Trace.WriteLine(string.Format("          push - Player: {0} at {1} trying {2} at {3}", playerOn.Name,
				                              playerOn.Robot.Location, plyrMoveRobot.Name, plyrMoveRobot.Robot.Location));
				if (MoveRobot(plyrMoveRobot, dir, origPlayer) == MOVE_RESULT.STUCK)
				{
					Trace.WriteLine(string.Format("          push failed - Player: {0} at {1} blocked by {2} at {3}",
					                              playerOn.Name, playerOn.Robot.Location, plyrMoveRobot.Name,
					                              plyrMoveRobot.Robot.Location));
					ValidateData();
					return MOVE_RESULT.STUCK;
				}
				origPlayer.Score += 2;
				if (plyrMoveRobot.Mode == Player.MODE.DEAD || plyrMoveRobot.Mode == Player.MODE.DESTROYED)
					origPlayer.Score += 5;
				Trace.WriteLine(string.Format("          push successful - Player: {0} at {1} moved {2} at {3}",
				                              playerOn.Name, playerOn.Robot.Location, plyrMoveRobot.Name,
				                              plyrMoveRobot.Robot.Location));
				ValidateData();
			}
			playerOn.Robot.Location = new BoardLocation(mp.Location.MapPosition, playerOn.Robot.Location.Direction);
			return MOVE_RESULT.OK;
		}

		// board (conveyor and gear) movement.
		private void ExecuteMoveBoard()
		{

			Trace.WriteLine("Conveyor and gear moves:");
			// We move if the dest is a conveyor or it's unoccupied. 
			// bugbug - The unoccupied test works for the one map we have - the one conveyor exit square has a wall after it.
			List<Player> plyrMoveBelt = Players.Where(playerInternal => playerInternal.IsVisible).ToList();
			for (int level = 2; level > 0; level--)
				foreach (Player plyrOn in plyrMoveBelt)
				{
					// needs to be on a belt - and we do the 2 move, then all
					MapSquare sq = MainMap.GetSquare(plyrOn.Robot.Location.MapPosition);
					if ((sq.Conveyor == null) || (sq.Conveyor.Speed < level))
						continue;

					Utilities.MovePoint mp = Utilities.Move(MainMap, plyrOn.Robot.Location.MapPosition, sq.Conveyor.Direction);
					MapSquare sqDest = MainMap.GetSquare(mp.Location.MapPosition);
					if (sqDest.Type == MapSquare.TYPE.CONVEYOR_BELT)
					{
						// the turn is based on the direction entered and the exit direction
						MapSquare.DIRECTION dirEnter = Utilities.MoveDirection(plyrOn.Robot.Location.MapPosition, mp.Location.MapPosition);
						BoardLocation dest = new BoardLocation(mp.Location.MapPosition, plyrOn.Robot.Location.Direction);
						dest = dest.Rotate((int)sqDest.Conveyor.Direction - (int)dirEnter);

						Trace.WriteLine(string.Format("     conveyor - Player: {0} at {1} moved to {2}", plyrOn.Name,
						                              plyrOn.Robot.Location, dest));
						plyrOn.Robot.Location = dest;
						continue;
					}
					// we're going off the belt
					Player plyrDestRobot =
						Players.Where(pl => (pl.IsVisible) && (pl.Robot.Location.MapPosition == mp.Location.MapPosition)).FirstOrDefault();
					if (plyrDestRobot != null)
					{
						Trace.WriteLine(string.Format("     conveyor - Player: {0} at {1} cannot be moved", plyrOn.Name,
						                              plyrOn.Robot.Location));
						continue;
					}
					BoardLocation location = new BoardLocation(mp.Location.MapPosition, plyrOn.Robot.Location.Direction);
					Trace.WriteLine(string.Format("     conveyor - Player: {0} at {1} moved off the belt to {2}",
					                              plyrOn.Name,
												  plyrOn.Robot.Location, location));
					Trap.trap(location.Direction != plyrOn.Robot.Location.Direction);
					plyrOn.Robot.Location = location;
				}
			// have to validate after because we move on top of each other handling the conveyor belt
			ValidateData();

			List<Player> plyrMoveGears = (from plyrOn in Players
			                                      where plyrOn.IsVisible
			                                      let sq = MainMap.GetSquare(plyrOn.Robot.Location.MapPosition)
			                                      where
			                                      	((sq.Type == MapSquare.TYPE.ROTATE_CLOCKWISE) ||
			                                      	 (sq.Type == MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE))
			                                      select plyrOn).ToList();
			foreach (Player plyrOn in plyrMoveGears)
			{
				MapSquare sq = MainMap.GetSquare(plyrOn.Robot.Location.MapPosition);
				plyrOn.Robot.Location = plyrOn.Robot.Location.Rotate(sq.Type == MapSquare.TYPE.ROTATE_CLOCKWISE ? 1 : -1);
				Trace.WriteLine(string.Format("     gear - Player: {0} turned to {1}", plyrOn.Name,
				                              plyrOn.Robot.Location));
				ValidateData();
			}
		}

		// lasers fire.
		private void ExecuteFire()
		{

			Trace.WriteLine("Fire lasers:");
			int numAlive = Players.Count(pl => pl.IsVisible);

			// robots shoot
			bool fired = false;
			foreach (Player playerOn in Players)
			{
				// we do this instead of a LINQ where because one firing can kill a latter robot.
				if (playerOn.Mode != Player.MODE.ACTIVE)
					continue;

				if (FireLaser(playerOn.Robot.Location, playerOn))
					fired = true;
			}
			// lasers shoot
			foreach (Laser laserOn in MainMap.Lasers)
				if (FireLaser(laserOn.Location, null))
					fired = true;
			if (fired && PlaySounds)
				laserPlayer.Play();

			if (Players.Count(pl => pl.IsVisible) < numAlive)
				if (PlaySounds)
					explosionPlayer.Play();
		}

		private struct LaserMove
		{
			internal readonly MapSquare.SIDE wallExit, wallEnter;
			internal readonly int xAdd, yAdd;

			public LaserMove(MapSquare.SIDE wallExit, MapSquare.SIDE wallEnter, int xAdd, int yAdd)
			{
				this.wallExit = wallExit;
				this.wallEnter = wallEnter;
				this.xAdd = xAdd;
				this.yAdd = yAdd;
			}
		}

		// DIRECTION order - NESW
		private static readonly LaserMove[] laserMove = {
		                                                	new LaserMove(MapSquare.SIDE.NORTH, MapSquare.SIDE.SOUTH, 0, -1),
		                                                	new LaserMove(MapSquare.SIDE.EAST, MapSquare.SIDE.WEST, 1, 0),
		                                                	new LaserMove(MapSquare.SIDE.SOUTH, MapSquare.SIDE.NORTH, 0, 1),
		                                                	new LaserMove(MapSquare.SIDE.WEST, MapSquare.SIDE.EAST, -1, 0)
		                                                };

		private bool FireLaser(BoardLocation location, Player firingPlayer)
		{

			LaserMove lm = laserMove[(int) location.Direction];
			int x = location.MapPosition.X;
			int y = location.MapPosition.Y;
			bool firstSquare = true;
			bool fired = false;

			while ((0 <= x) && (x < MainMap.Width) && (0 <= y) && (y < MainMap.Height))
			{
				MapSquare sq = MainMap.Squares[x][y];
				// can we move into this square?
				if ((!firstSquare) && ((sq.Walls & lm.wallEnter) != 0))
					break;

				// robot to hit? (can be us if isLaser is true)
				Point pt = new Point(x, y);
				Player plyrTargetRobot =
					Players.Where(pl => (pl.IsVisible) && (pl.Robot.Location.MapPosition == pt)).FirstOrDefault();
				if ((plyrTargetRobot != null) && ((firingPlayer == null) || (!firstSquare)))
				{
					// call this before IncreaseDamage because if it's killed it is moved to -1, -1
					Explosion expl = new Explosion(framework.frameTicks, plyrTargetRobot.Robot.Location.MapPosition);
					framework.sprites.Add(expl);
					framework.laserBeams.Add(new LaserBeam(location.MapPosition, plyrTargetRobot.Robot.Location.MapPosition, firingPlayer == null));

					plyrTargetRobot.IncreaseDamage();
					fired = true;
					if (firingPlayer != null)
						firingPlayer.Score += 1;

					Trace.WriteLine(string.Format("     laser - Player: {0} at {1} hit by laser at {2}, damage {3}, lives {4}",
					                              plyrTargetRobot.Name, plyrTargetRobot.Robot.Location,
					                              location, plyrTargetRobot.Damage, plyrTargetRobot.Lives));
					if (plyrTargetRobot.Mode == Player.MODE.DEAD)
						framework.mainWindow.StatusMessage(string.Format("Player {0} has been killed", plyrTargetRobot.Name));
					ValidateData();
					break;
				}

				// can we move out of this square?
				if ((sq.Walls & lm.wallExit) != 0)
					break;
				x += lm.xAdd;
				y += lm.yAdd;
				firstSquare = false;
			}
			return fired;
		}

		// end of each phase - on a flag or repair square.
		private void ExecuteFlagAndArchive()
		{

			// if on a flag, mark it; update archive square.
			foreach (Player playerOn in Players)
			{
				// we do this instead of a LINQ where because one firing can kill a latter robot.
				if (playerOn.Mode != Player.MODE.ACTIVE)
					continue;

				MapSquare sq = MainMap.GetSquare(playerOn.Robot.Location.MapPosition);
				if (sq.Type == MapSquare.TYPE.FLAG)
				{
					playerOn.TouchedFlag(playerOn.Robot.Location.MapPosition);
					continue;
				}

				if (sq.Type == MapSquare.TYPE.REPAIR)
				{
					playerOn.SetArchive(playerOn.Robot.Location.MapPosition);
					continue;
				}
			}
		}

		// end of turn - power up/down, un-destroy, repair
		private void ExecuteEndTurn()
		{

			phaseOn = PHASE.GET_TURN;

			foreach (Player playerOn in Players)
			{
				ValidateData();
				if (playerOn.Mode == Player.MODE.DEAD)
					continue;

				// power down - after all moves, was not killed
				if ((playerOn.Mode == Player.MODE.ACTIVE) && (playerOn.PowerMode == Player.POWER_MODE.ANNOUNCED))
				{
					playerOn.PowerDown();
					Trace.WriteLine(string.Format("power down - Player: {0}, damage {1}", playerOn.Name, playerOn.Damage));
				}
				else
					// power up - still alive
					if (playerOn.PowerMode == Player.POWER_MODE.DOWN)
					{
						if (--playerOn.PowerDownTurnsRemaining > 0)
							continue;
						playerOn.PowerUp();
						Trace.WriteLine(string.Format("power up - Player: {0}, damage {1}", playerOn.Name, playerOn.Damage));
						if (playerOn.Mode == Player.MODE.DEAD)
							continue;
					}

				// we bring the robot back in at the end of the turn if it was destroyed.
				if (playerOn.Mode == Player.MODE.DESTROYED)
				{
					// is the archive available?
					List<Point> reEnter = new List<Point>();
					Player plyrDestRobot =
						Players.Where(pl => (pl.IsVisible) && (pl.Robot.Location.MapPosition == playerOn.Archive)).FirstOrDefault();
					if (plyrDestRobot == null)
						reEnter.Add(playerOn.Archive);
					else
					{
						// ok, get all around the archive that aren't occupied.
						for (int x = playerOn.Archive.X - 1; x <= playerOn.Archive.X + 1; x++)
							for (int y = playerOn.Archive.Y - 1; y <= playerOn.Archive.Y + 1; y++)
								if ((0 <= x) && (x < MainMap.Width) && (0 <= y) && (y < MainMap.Height))
								{
									Point pt = new Point(x, y);
									plyrDestRobot = Players.Where(pl => (pl.IsVisible) && (pl.Robot.Location.MapPosition == pt)).FirstOrDefault();
									if (plyrDestRobot == null)
										reEnter.Add(pt);
								}
					}
					playerOn.Robot.Location = new BoardLocation(reEnter[0], MapSquare.DIRECTION.NORTH); // until we get a reply.
					playerOn.UnDestroy();
					Trace.WriteLine(string.Format("un-destroy - Player: {0}, Lives {1}, Location(s) {2}", playerOn.Name,
												  playerOn.Lives, reEnter.ToArray()));

					playerOn.WaitingForReply = Player.COMM_MODE.WAITING_FOR_LOCATION;
					// we set this before the call requesting the position to avoid getting a reply before we set it.
					if (playerOn.TcpGuid != null)
						phaseOn = PHASE.WAITING_ON_ARCHIVE;
					framework.RequestStartPosition(playerOn, reEnter, false);
					continue;
				}

				MapSquare sq = MainMap.GetSquare(playerOn.Robot.Location.MapPosition);
				if ((sq.Type == MapSquare.TYPE.REPAIR) && IsRepairTurn) 
				{
					playerOn.Repair(playerOn.Robot.Location.MapPosition);
					Trace.WriteLine(string.Format("repair - Player: {0}, damage {1}", playerOn.Name, playerOn.Damage));
				}
				ValidateData();
			}
			cardOn = 0;

			if (phaseOn != PHASE.WAITING_ON_ARCHIVE) 
				return;

			// set up timeout as we're waiting. Check if we got everything.
			framework.WaitingForReentry();
			if (!Players.Any(pl => pl.WaitingForReply != Player.COMM_MODE.READY))
			{
				Trap.trap();
				phaseOn = PHASE.GET_TURN;
			}
		}

		public void PlayerSetArchive(Player player, BoardLocation location)
		{
			player.Robot.Location = location;
			if (!Players.Any(pl => pl.Robot.Location.IsNull && pl.TcpGuid != null))
				phaseOn = PHASE.GET_TURN;
		}

		#endregion

		#region testing

#if DEBUG
		private void ValidateData()
		{

			bool error = false;
			foreach (Player playerOn in Players)
			{
				if ((playerOn.Damage < 0) || (10 < playerOn.Damage))
				{
					Trace.WriteLine(string.Format("ERROR - player {0} has a damage level of {1}", playerOn.Name,
					                              playerOn.Damage));
					error = true;
				}
				if ((playerOn.Lives < 0) || (3 < playerOn.Lives))
				{
					Trace.WriteLine(string.Format("ERROR - player {0} has a life level of {1}", playerOn.Name,
					                              playerOn.Lives));
					error = true;
				}
				if (playerOn.Score < 0)
				{
					Trace.WriteLine(string.Format("ERROR - player {0} has a score of {1}", playerOn.Name, playerOn.Score));
					error = true;
				}

				if ((TurnOn > 1) && (playerOn.Cards.Count != (playerOn.Mode == Player.MODE.DEAD ? 0 : Framework.NUM_PHASES)))
				{
					Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} has {2} cards", playerOn.Name,
												  playerOn.Mode, playerOn.Cards.Count));
					error = true;
				}


				if ((playerOn.Mode == Player.MODE.ACTIVE) || (playerOn.Mode == Player.MODE.POWER_DOWN))
				{
					if ((playerOn.Robot.Location.MapPosition.X < 0) || (MainMap.Width <= playerOn.Robot.Location.MapPosition.X) ||
					    (playerOn.Robot.Location.MapPosition.Y < 0) || (MainMap.Height <= playerOn.Robot.Location.MapPosition.Y))
					{
						Trace.WriteLine(string.Format("ERROR - player {0} off board at {1}", playerOn.Name,
						                              playerOn.Robot.Location));
						error = true;
					}

					if (playerOn.Damage == 10)
					{
						Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} has a damage level of 10",
						                              playerOn.Name, playerOn.Mode));
						error = true;
					}
					if (playerOn.Lives == 0)
					{
						Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} has a life level of 0", playerOn.Name,
						                              playerOn.Mode));
						error = true;
					}

					// only 1 at this location on the map
					List<Player> stackedPlayers =
						Players.Where(pl => pl.IsVisible && (pl.Robot.Location.MapPosition == playerOn.Robot.Location.MapPosition)).ToList
							();
					if (stackedPlayers.Count > 1)
					{
						StringBuilder buf =
							new StringBuilder(string.Format("ERROR - map location {0} has players: ", playerOn.Robot.Location.MapPosition));
						foreach (Player pl in stackedPlayers)
							buf.Append(string.Format("{0}, ", pl.Name));
						Trace.WriteLine(buf);
						error = true;
					}
				}

					// destroyed or dead
				else
				{
					if ((playerOn.Robot.Location.MapPosition.X != -1) || (playerOn.Robot.Location.MapPosition.Y != -1))
					{
						Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} on board at {2}", playerOn.Name,
						                              playerOn.Mode,
						                              playerOn.Robot.Location));
						error = true;
					}

					if ((playerOn.Mode == Player.MODE.DESTROYED) && (playerOn.Lives == 0))
					{
						Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} has a life level of 0", playerOn.Name,
						                              playerOn.Mode));
						error = true;
					}
					if ((playerOn.Mode == Player.MODE.DEAD) && (playerOn.Lives != 0))
					{
						Trace.WriteLine(string.Format("ERROR - player {0} in mode {1} has a life level of 0", playerOn.Name,
						                              playerOn.Mode));
						error = true;
					}
				}
			}
			Trap.trap(error);
		}
#else
		private void ValidateData()
		{
		}
#endif

		#endregion

	}
}
