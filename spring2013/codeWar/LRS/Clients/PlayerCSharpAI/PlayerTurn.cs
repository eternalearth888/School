// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Collections.Generic;
using System.Text;
using System.Xml.Linq;
using PlayerCSharpAI.api;

namespace PlayerCSharpAI
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
		public PlayerTurn(List<Card> cards, bool powerDown)
		{
			Cards = cards ?? new List<Card>();
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

		/// <summary>
		/// Create the XML of the turn.
		/// </summary>
		public XElement XML
		{
			get
			{
				XElement xmlTurn = new XElement("turn", new XAttribute("power-down", IsPowerDown));
				XElement xmlCards = new XElement("cards");
				foreach (Card cardOn in Cards)
					xmlCards.Add(cardOn.XML);
				xmlTurn.Add(xmlCards);
				return xmlTurn;
			}
		}

		/// <summary>
		/// User friendly display.
		/// </summary>
		/// <returns>User friendly display.</returns>
		public override string ToString()
		{
			StringBuilder buf = new StringBuilder("Turn: Cards[");
			foreach (Card cardOn in Cards)
				buf.Append(cardOn + ", ");
			if (Cards.Count > 0)
				buf.Remove(buf.Length - 2, 2);
			buf.Append(']');
			if (IsPowerDown)
				buf.Append(" PowerDown");
			return buf.ToString();
		}
	}
}
