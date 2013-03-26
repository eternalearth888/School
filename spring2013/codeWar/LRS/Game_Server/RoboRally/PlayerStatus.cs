// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Drawing;
using System.Windows.Forms;
using RoboRallyNet.game_engine;

namespace RoboRallyNet
{
	/// <summary>
	/// The window that displays a player's status.
	/// </summary>
	internal partial class PlayerStatus : UserControl
	{
		private static readonly Bitmap[] avatars = new [] { Avatars.avatar1, Avatars.avatar2, Avatars.avatar3, Avatars.avatar4 };
		private static int nextAvatar;

		/// <summary>
		/// Create the window.
		/// </summary>
		/// <param name="player">The player this window is for.</param>
		public PlayerStatus(Player player)
		{
			InitializeComponent();
			Player = player;
			if (player == null) 
				return;

			PlayerGuid = player.Guid;
		}

		/// <summary>
		/// The player Guid for this status.
		/// </summary>
		public string PlayerGuid { get; private set; }

		/// <summary>
		/// The player this is showing status for.
		/// </summary>
		public Player Player { get; private set; }

		/// <summary>
		/// Redraw this window. Call when status has changed.
		/// </summary>
		public void UpdateStats()
		{
			labelScore.Text = Player.Score.ToString();
			Invalidate(true);
		}

		private void PlayerStatus_Load(object sender, System.EventArgs e)
		{
			BackColor = Player.SpriteColor;
			if ((Player.Avatar != null) && (Player.Avatar.Width == 32) && (Player.Avatar.Height == 32))
				pictureBoxAvatar.Image = Player.Avatar;
			else
			{
				pictureBoxAvatar.Image = avatars[nextAvatar++];
				if (nextAvatar >= avatars.Length)
					nextAvatar = 0;
			}
			pictureBoxRobot.Image = Player.Robot.Bitmaps[0];
			labelName.Text = Player.Name;
		}

		private readonly Bitmap[] cards = { Status.bu, Status.m1, Status.m2, Status.m3, Status.tl, Status.tr, Status.ut };
		private readonly Bitmap[] cardsGrey = { Status.bu_grey, Status.m1_grey, Status.m2_grey, Status.m3_grey, Status.tl_grey, Status.tr_grey, Status.ut_grey };

		private void PlayerStatus_Paint(object sender, PaintEventArgs pe)
		{
			// Life Tokens - 97, 4 - space = 3
			for (int ind = 0; ind < 3; ind++)
			{
				Bitmap bmp = Player.Lives > ind ? Status.star_green : Status.star_red;
				pe.Graphics.DrawImage(bmp, new Rectangle(97 + ind * (32 + 3), 4, 32, 32));
			}

			// flags - 205, 4 - space = 3
			for (int ind = 0; ind < Player.FlagStates.Count; ind++)
			{
				Bitmap bmp = Player.FlagStates[ind].Touched ? Status.flag_blue : Status.flag_yellow;
				pe.Graphics.DrawImage(bmp, new Rectangle(205 + ind * (32 + 3), 4, 32, 32));
			}

			// cards - 4, 60 - space = 6
			int indLock = 9 - Player.Damage;
			for (int ind=0; ind<Framework.NUM_PHASES; ind++)
			{
				if (ind >= Player.Cards.Count)
				{
					pe.Graphics.DrawImage(Status.empty_register, new Rectangle(4 + ind * (45 + 6), 60, 45, 65));
					continue;
				}
				int indBitmap = (int)Player.Cards[ind].Move;
				Bitmap bmp = (Player.Mode == Player.MODE.POWER_DOWN) ? cardsGrey[indBitmap] : (ind < indLock ? cards[indBitmap] : cardsGrey[indBitmap]);
				pe.Graphics.DrawImage(bmp, new Rectangle(4 + ind * (45 + 6), 60, 45, 65));
			}

			// damage - 4 + 5 * (24 + 7), 60 - space = 7 - 2 rows
			for (int ind = 0; ind < 10; ind++)
			{
				// grey starts on the right
				Bitmap bmp = ind >= (10 - Player.Damage) ? Status.warning_grey : Status.warning;
				int x = 159 + (ind % 5) * (24 + 7);
				int y = ind <= 4 ? 60 : 92;
				pe.Graphics.DrawImage(bmp, new Rectangle(x, y, 24, 24));
			}

			// power down - over card
			if (Player.Mode == Player.MODE.POWER_DOWN)
				pe.Graphics.DrawImage(Status.gear_add, new Rectangle(4 + (45 + 6), 60 + (65 - 48) / 2, 48, 48));
		}
	}
}
