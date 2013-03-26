// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using PlayerCSharpAI.api;

namespace PlayerCSharpAI.AI
{
	/// <summary>
	/// The sample C# AI. Start with this project but write your own code as this is a very simplistic implementation of the AI.
	/// </summary>
	public class MyPlayerBrain 
	{
		private const int NUM_CARDS = 1;

		private readonly string name = "Donald Knuth";
		private readonly string password = "Donald Knuth";
		private static readonly Random rand = new Random();

		public MyPlayerBrain(string name, string password)
		{
			if (name != null)
				this.name = name;
			if (password != null)
				this.password = password;
		}

		/// <summary>
		/// The name of the player.
		/// </summary>
		public string Name
		{
			get { return name; }
		}

		/// <summary>
		/// The communication password for this player.
		/// </summary>
		public string Password
		{
			get { return password; }
		}

		/// <summary>
		/// The avatar of the player. Must be 32 x 32.
		/// </summary>
		public byte[] Avatar
		{
			get {
				using (Stream avatar = Assembly.GetExecutingAssembly().GetManifestResourceStream("PlayerCSharpAI.AI.MyAvatar.png"))
				{
					if (avatar == null)
						return null;
					byte[] data = new byte[avatar.Length];
					avatar.Read(data, 0, data.Length);
					return data;
				}
			}
		}

		/// <summary>
		/// Called when your robot must be placed on the board. This is called at the start of the game and each time your robot dies.
		/// </summary>
		/// <param name="map">The game map. There will be no units on this map.</param>
		/// <param name="you">Your player object.</param>
		/// <param name="players">All players (including you).</param>
		/// <param name="robotStart">The position(s) on the map where you can place your robot. This will be a single point unless another robot is on your archive point.</param>
		/// <param name="gameStart">true if start of a game. false if re-entering the game.</param>
		/// <returns>Where to place your unit (location and direction.</returns>
		public BoardLocation Setup(GameMap map, Player you, List<Player> players, List<Point> robotStart, bool gameStart)
		{
			return new BoardLocation(robotStart[0], MapSquare.DIRECTION.NORTH);
		}

		/// <summary>
		/// Called each time the system needs another turn. If you do not return a valid turn, the game will randomly move one of your units.
		/// This call must return in under 1 second. If it has not returned in 1 second the call will be aborted and a random move will be assigned.
		/// </summary>
		/// <param name="map">The game map with all units on it.</param>
		/// <param name="you">Your player object. This is created for each call.</param>
		/// <param name="allPlayers">All players including you. This is created for each call.</param>
		/// <param name="cards">The cards you get to pick from. This does not include locked cards.</param>
		/// <returns>Your requested turn.</returns>
		public PlayerTurn Turn(GameMap map, Player you, List<Player> allPlayers, List<Card> cards)
		{

			// if hurt bad, consider power down
			bool powerDown = false;
			if ((you.Damage > 5) && (rand.Next(4) == 0))
				powerDown = true;

			// get 40 sets, pick the one that's closest to the flag (middle of the board if got all flags)
			List<Card> best = null;
			int bestDiff = int.MaxValue;
			int okDiff = rand.Next(0, 3);
			FlagState fs = you.FlagStates.FirstOrDefault(fsOn => !fsOn.Touched);
			Point ptFlag = fs == null ? new Point(map.Width / 2, map.Height / 2) : fs.Position;
			for (int turnOn = 0; turnOn < 40; turnOn++)
			{
				// pick NUM_CARDS (or fewer if locked) random cards
				List<Card> moveCards = new List<Card>();
				bool[] cardUsed = new bool[cards.Count];
				for (int ind = 0; ind < NUM_CARDS - you.NumLockedCards; ind++)
					for (int iter = 0; iter < 100; iter++) // in case can't work it with these cards
						{
							int index = rand.Next(cards.Count);
							if (cardUsed[index])
								continue;
							moveCards.Add(cards[index]);
							cardUsed[index] = true;
							break;
						}

				// add in the locked cards
				for (int ind = NUM_CARDS - you.NumLockedCards; ind < NUM_CARDS; ind++)
					moveCards.Add(you.Cards[ind]);

				// If all we have are rotates, we add in a move forward 1 so that a card that is a turn can then take into account next time we get a forward 1.
				bool addMove = moveCards.All(card => card.IsRotate);
				if (addMove)
					moveCards.Add(new Card(Card.ROBOT_MOVE.FORWARD_ONE, 500));

				// run it 
				Utilities.MovePoint mp = Utilities.CardDestination(map, you.Robot.Location, moveCards);

				// if it kills us we don't want it
				if (mp.Dead)
					continue;

				// if better than before, use it
				if (addMove)
					moveCards.RemoveAt(moveCards.Count - 1);
				int diff = Math.Abs(ptFlag.X - mp.Location.MapPosition.X) + Math.Abs(ptFlag.Y - mp.Location.MapPosition.Y);
				if (diff <= okDiff)
					return new PlayerTurn(new List<Card>(moveCards), powerDown);
				if (diff < bestDiff)
				{
					bestDiff = diff;
					best = moveCards;
				}
			}

			return new PlayerTurn(best == null ? new List<Card>() : new List<Card>(best), powerDown);
		}
	}
}
