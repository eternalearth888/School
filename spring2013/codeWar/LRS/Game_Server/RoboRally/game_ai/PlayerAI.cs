using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using RoboRallyNet.game_engine;

namespace RoboRallyNet.game_ai
{
	/// <summary>
	/// A very simplistic implementation of the AI. This AI is used if we have less than 8 players.
	/// </summary>
	public class PlayerAI : Player
	{
		private readonly Random rand = new Random();

		public PlayerAI(string guid, string name, string password, Image avatar, Point archive, Robot robot, IEnumerable<Point> flags, Color spriteColor) : base(guid, name, password, avatar, archive, robot, flags, spriteColor)
		{
		}

		public PlayerAI(Player src, Point archive, Robot robot, Color spriteColor) : base(src, archive, robot, spriteColor)
		{
		}

		/// <summary>
		/// Called when your robot must be placed on the board. This is called at the start of the game and each time your robot dies.
		/// </summary>
		/// <param name="robotStart">The position(s) on the map where you can place your robot. This will be a single point unless another robot is on your archive point.</param>
		/// <returns>Where to place your unit (location and direction.</returns>
		public BoardLocation Setup(List<Point> robotStart)
		{
			return new BoardLocation(robotStart[0], MapSquare.DIRECTION.NORTH);
		}

		/// <summary>
		/// Called each time the system needs another turn. If you do not return a valid turn, the game will randomly move one of your units.
		/// This call must return in under 1 second. If it has not returned in 1 second the call will be aborted and a random move will be assigned.
		/// </summary>
		/// <param name="map">The game map with all units on it.</param>
		/// <param name="you">Your player object. This is created for each call.</param>
		/// <param name="cards">The cards you get to pick from. This does not include locked cards.</param>
		/// <returns>Your requested turn.</returns>
		public PlayerTurn Turn(GameMap map, Player you, List<Card> cards)
		{

			// get 40 sets, pick the one that's closest to the flag - center of map if flags all done
			List<Card> best = null;
			int bestDiff = int.MaxValue;
			int okDiff = rand.Next(0, 3);
			FlagState fs = you.FlagStates.FirstOrDefault(fsOn => !fsOn.Touched);
			Point ptFlag = fs == null ? new Point(map.Width / 2, map.Height / 2) : fs.Position;
			for (int turnOn = 0; turnOn < 40; turnOn++)
			{
				// pick 5 (or fewer if locked) random cards
				List<Card> moveCards = new List<Card>();
				bool[] cardUsed = new bool[cards.Count];
				for (int ind = 0; ind < Framework.NUM_PHASES - you.NumLockedCards; ind++)
					for (int iter = 0; iter < 100; iter++) // in case can't work it with these cards
					{
						Trap.trap(iter > 20);
						int index = rand.Next(cards.Count);
						if (cardUsed[index]) 
							continue;
						moveCards.Add(cards[index]);
						cardUsed[index] = true;
						break;
					}

				// add in the locked cards
				for (int ind = Framework.NUM_PHASES - you.NumLockedCards; ind < Framework.NUM_PHASES; ind++)
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
					return new PlayerTurn(moveCards, false);
				if (diff < bestDiff)
				{
					bestDiff = diff;
					best = moveCards;
				}
			}

			return new PlayerTurn(best, false);
		}
	}
}
