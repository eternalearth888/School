// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Collections.Generic;
using RoboRallyNet.game_engine;

namespace RoboRallyNet.game_ai
{

	/// <summary>
	/// A requested move for a player's turn.
	/// </summary>
	public class PlayerTurn
	{
		/// <summary>
		/// Return your turn. If you have locked cards will only use the first N (unlocked) cards returned. If you do not return 
		/// enough cards, random cards will be assigned. Locked cards are the last N cards from the previous turn.
		/// </summary>
		/// <param name="cards">Your unlocked cards.</param>
		/// <param name="powerDown">true if power down at the end of this turn.</param>
		public PlayerTurn(IEnumerable<Card> cards, bool powerDown)
		{
			Cards = cards == null ? new List<Card>() : new List<Card>(cards);
			IsPowerDown = powerDown;
		}

		/// <summary>
		/// The cards requested for the upcoming turn. If your Damage is greater than 4 then not all 5 of these will be used, but you
		/// may return 5. The extras will be ignored.
		/// </summary>
		public List<Card> Cards { get; private set; }

		/// <summary>
		/// Return true to power down at the end of the upcoming turn. You also need to return Cards because the power down occurs
		/// AFTER this turn!
		/// </summary>
		public bool IsPowerDown { get; private set; }
	}
}
