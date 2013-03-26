using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;
using RoboRallyNet.game_engine;

namespace RoboRallyNet
{
	/// <summary>
	/// The main window.
	/// </summary>
	public partial class MainWindow : Form, IUserDisplay
	{
		private readonly List<PlayerStatus> playerStats = new List<PlayerStatus>();
		private DataTable table;

		/// <summary>
		/// Create the window.
		/// </summary>
		public MainWindow()
		{
			InitializeComponent();
		}

		private void MainWindow_Load(object sender, EventArgs e)
		{
			// initialize engine
			GameFramework = new Framework(this);

			UpdateMenu();

		}

		/// <summary>
		/// The engine that operates the game.
		/// </summary>
		internal Framework GameFramework { get; private set; }

		/// <summary>
		/// Used for Invoke when we get TCP callbacks.
		/// </summary>
		public Control CtrlForInvoke
		{
			get { return this; }
		}

		private void toolStripButtonJoin_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Join");
			if (MessageBox.Show(this, @"Do you want to end this series and drop all players?", @"RoboRallyNet", MessageBoxButtons.YesNo) != DialogResult.Yes)
				return;
			GameFramework.RestartJoins();
			UpdateMenu();
		}

		private void toolStripButtonClosed_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Locked");
			if (GameFramework.GameEngine.Players.Count < 8)
				if (MessageBox.Show(this, @"Have all players joined for this series?", @"RoboRallyNet", MessageBoxButtons.YesNo) != DialogResult.Yes)
					return;
			GameFramework.CloseJoins();
			UpdateMenu();
		}

		/// <summary>
		/// The play button was clicked.
		/// </summary>
		private void Play_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Play");
			GameFramework.Play();
			UpdateMenu();
		}

		private void toolStripButtonStep_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Step");
			GameFramework.Step();
			UpdateMenu();
		}

		/// <summary>
		/// The pause button was clicked.
		/// </summary>
		private void Pause_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Pause");
			GameFramework.PauseAtEndOfTurn();
			UpdateMenu();
		}

		/// <summary>
		/// The stop button was clicked.
		/// </summary>
		private void Stop_Click(object sender, EventArgs e)
		{
			Trace.WriteLine("menu: Stop");
			if (MessageBox.Show(this, @"Do you want to end this run?", @"RoboRallyNet", MessageBoxButtons.YesNo) != DialogResult.Yes)
				return;
			GameFramework.Stop();
			UpdateMenu();
		}

		private void toolStripButtonSpeed_Click(object sender, EventArgs e)
		{

			Trace.WriteLine("menu: Speed");
			using (GameSpeed dlg = new GameSpeed(GameFramework.MovesPerSecond))
			{
				if (dlg.ShowDialog() == DialogResult.OK)
					GameFramework.MovesPerSecond = dlg.MovesPerSecond;
			}
			UpdateMenu();
		}

		private void toolStripButtonTimeout_Click(object sender, EventArgs e)
		{

			Trace.WriteLine("menu: Timeout");
			using (ClientTimeout dlg = new ClientTimeout(GameFramework.TurnTimeoutSeconds))
			{
				if (dlg.ShowDialog() == DialogResult.OK)
					GameFramework.TurnTimeoutSeconds = dlg.TimeoutSeconds;
			}
			UpdateMenu();
		}

		private void toolStripButtonMute_Click(object sender, EventArgs e)
		{

			Trace.WriteLine("menu: Speed");
			GameFramework.GameEngine.PlaySounds = ! GameFramework.GameEngine.PlaySounds;
			toolStripButtonMute.Checked = !GameFramework.GameEngine.PlaySounds;
		}

		/// <summary>
		/// Update the main window menu.
		/// </summary>
		public void UpdateMenu()
		{
			toolStripButtonJoinOpened.Enabled = GameFramework.Mode == Framework.COMM_STATE.GAME_OVER;
			toolStripButtonJoinClosed.Enabled = GameFramework.Mode == Framework.COMM_STATE.ACCEPTING_JOINS && GameFramework.GameEngine.Players.Count > 0;
			toolStripButtonPlay.Enabled = GameFramework.Mode == Framework.COMM_STATE.READY_TO_START || GameFramework.Mode == Framework.COMM_STATE.PAUSED || 
				GameFramework.Mode == Framework.COMM_STATE.GAME_OVER;
			toolStripButtonStep.Enabled = GameFramework.Mode == Framework.COMM_STATE.READY_TO_START || GameFramework.Mode == Framework.COMM_STATE.PAUSED || 
				GameFramework.Mode == Framework.COMM_STATE.GAME_OVER;
			toolStripButtonPause.Enabled = GameFramework.Mode == Framework.COMM_STATE.ACCEPTING_TURN || GameFramework.Mode == Framework.COMM_STATE.PROCESSING_TURN || 
				GameFramework.Mode == Framework.COMM_STATE.ACCEPTING_REENTRY;
			toolStripButtonStop.Enabled = GameFramework.Mode == Framework.COMM_STATE.ACCEPTING_TURN || GameFramework.Mode == Framework.COMM_STATE.PROCESSING_TURN ||
				GameFramework.Mode == Framework.COMM_STATE.ACCEPTING_REENTRY || GameFramework.Mode == Framework.COMM_STATE.PAUSED;
		}

		/// <summary>
		/// Got a close window event. Ask for confirmation if a game is in process.
		/// </summary>
		private void GameDisplay_FormClosing(object sender, FormClosingEventArgs fcea)
		{
			if ((GameFramework.Mode != Framework.COMM_STATE.GAME_OVER) && (MessageBox.Show(this, @"Do you want to close the game?", @"RoboRallyNet", MessageBoxButtons.YesNo) != DialogResult.Yes))
				fcea.Cancel = true;

			if (! fcea.Cancel)
				GameFramework.tcpServer.CloseAllConnections();
		}

		/// <summary>
		/// The app is exiting - close all connections.
		/// </summary>
		private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
		{
			GameFramework.tcpServer.CloseAllConnections();
		}

		/// <summary>
		/// Starting a game.
		/// </summary>
		public void SetupGame()
		{

			// if have stats windows - dispose them
			while (playerStats.Count > 0)
			{
				PlayerStatus statOn = playerStats[0];
				playerStats.RemoveAt(0);
				panelPlayers.Controls.Remove(statOn);
				statOn.Dispose();
			}

			// create player stats windows
			NewPlayerAdded();
		}

		/// <summary>
		/// New player added to the game
		/// </summary>
		public void NewPlayerAdded()
		{

			// create player stats windows
			int top = 0;
			int winOn = 0;
			bool firstTime = true;
			foreach (Player playerOn in GameFramework.GameEngine.Players)
			{
				if (winOn < playerStats.Count)
				{
					winOn++;
					continue;
				}

				PlayerStatus ps = new PlayerStatus(playerOn) { Width = panelPlayers.Width / 2 };

				// set up top position
				if (firstTime)
				{
					firstTime = false;
					top = (winOn / 2)*ps.Height;
				}

				if ((winOn & 1) == 0)
				{
					ps.Top = top;
					ps.Left = 0;
				}
				else
				{
					ps.Top = top;
					ps.Left = panelPlayers.Width / 2;
					top += ps.Height;
				}
				winOn++;
				playerStats.Add(ps);
				panelPlayers.Controls.Add(ps);
			}

			UpdateMap();
			UpdatePlayers();
		}

		/// <summary>
		/// Update the map window.
		/// </summary>
		public void UpdateMap()
		{
			mapDisplay.Invalidate();
			mapDisplay.Update();
		}

		/// <summary>
		/// Update (re-draw) the player status windows.
		/// </summary>
		public void UpdatePlayers()
		{

			if (playerStats.Count == 0)
				return;

			foreach (PlayerStatus ps in playerStats)
				ps.UpdateStats();
			panelPlayers.Invalidate();
			panelPlayers.Update();

			UpdateScoreboard();
		}

		/// <summary>
		/// Called to delete all player status windows the player status windows.
		/// </summary>
		public void ResetPlayers()
		{

			if (table != null)
			{
				table.Dispose();
				table = null;
				UpdateScoreboard();
			}

			if (playerStats.Count != 0)
			{
				foreach (PlayerStatus ps in playerStats)
					ps.Dispose();
				playerStats.Clear();

				panelPlayers.Invalidate();
				panelPlayers.Update();
			}
		}

		private void UpdateScoreboard()
		{

			if (playerStats.Count == 0)
				return;

			bool incGameOn = GameFramework.Mode != Framework.COMM_STATE.GAME_OVER;

			// create a new table (new game or player added)?
			if ((table == null) || (table.Rows.Count != playerStats.Count) ||
									(table.Columns.Count != playerStats[0].Player.Scoreboard.Count + (incGameOn ? 1 : 0) + 2))
			{

				table = new DataTable();
				table.Columns.Add("Player", typeof (string));
				for (int ind = 0; ind < playerStats[0].Player.Scoreboard.Count + (incGameOn ? 1 : 0); ind++)
					table.Columns.Add("Game " + (ind + 1), typeof (int));
				table.Columns.Add("Total", typeof (int));
				foreach (PlayerStatus plyrOn in playerStats.OrderBy(pl => pl.Player.Name))
				{
					List<object> cells = new List<object> {plyrOn.Player.Name};
					int total = 0;
					foreach (int score in plyrOn.Player.Scoreboard)
					{
						cells.Add(score);
						total += score;
					}
					if (incGameOn)
					{
						cells.Add(plyrOn.Player.Score);
						total += plyrOn.Player.Score;
					}
					cells.Add(total);
					table.Rows.Add(cells.ToArray());
				}

				dataGridView.SuspendLayout();
				dataGridView.DataSource = null;
				dataGridView.DataSource = table;
				dataGridView.ResumeLayout();
				return;
			}

			// update existing table
			foreach (PlayerStatus plyrOn in playerStats.OrderBy(pl => pl.Player.Name))
			{
				DataRow row = table.Rows.Cast<DataRow>().First(rowOn => (string) rowOn[0] == plyrOn.Player.Name);
				int total = 0;
				int colOn = 1;
				foreach (int score in plyrOn.Player.Scoreboard)
				{
					row[colOn++] = score;
					total += score;
				}
				if (incGameOn)
				{
					row[colOn++] = plyrOn.Player.Score;
					total += plyrOn.Player.Score;
				}
				row[colOn] = total;
			}
		}

		/// <summary>
		/// Adds a message to the status window.
		/// </summary>
		/// <param name="message">The message to add.</param>
		public void StatusMessage(string message)
		{
			listBoxStatus.Items.Add(message);
			listBoxStatus.TopIndex = listBoxStatus.Items.Count - 1;
		}

		/// <summary>
		/// Set the turn or phase number increases.
		/// </summary>
		/// <param name="turn">The turn number.</param>
		/// <param name="phase">The phase number.</param>
		public void TurnNumber(int turn, int phase)
		{
			Text  = string.Format("RoboRally - Turn: {0}", turn);
		}

	}
}
