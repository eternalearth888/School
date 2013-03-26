namespace RoboRallyNet
{
	partial class MainWindow
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
			this.panelRight = new System.Windows.Forms.Panel();
			this.panelBottom = new System.Windows.Forms.Panel();
			this.dataGridView = new System.Windows.Forms.DataGridView();
			this.panelPlayers = new System.Windows.Forms.Panel();
			this.listBoxStatus = new System.Windows.Forms.ListBox();
			this.toolStripMainMenu = new System.Windows.Forms.ToolStrip();
			this.toolStripButtonJoinOpened = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonJoinClosed = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripButtonPlay = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonStep = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonPause = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonStop = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripButtonSpeed = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonTimeout = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonMute = new System.Windows.Forms.ToolStripButton();
			this.panelLeft = new System.Windows.Forms.Panel();
			this.mapDisplay = new RoboRallyNet.MapDisplay();
			this.panelRight.SuspendLayout();
			this.panelBottom.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
			this.toolStripMainMenu.SuspendLayout();
			this.panelLeft.SuspendLayout();
			this.SuspendLayout();
			// 
			// panelRight
			// 
			this.panelRight.Controls.Add(this.panelBottom);
			this.panelRight.Controls.Add(this.panelPlayers);
			this.panelRight.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelRight.Location = new System.Drawing.Point(421, 25);
			this.panelRight.Name = "panelRight";
			this.panelRight.Size = new System.Drawing.Size(629, 831);
			this.panelRight.TabIndex = 0;
			// 
			// panelBottom
			// 
			this.panelBottom.Controls.Add(this.dataGridView);
			this.panelBottom.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panelBottom.Location = new System.Drawing.Point(0, 516);
			this.panelBottom.Name = "panelBottom";
			this.panelBottom.Size = new System.Drawing.Size(629, 315);
			this.panelBottom.TabIndex = 3;
			// 
			// dataGridView
			// 
			this.dataGridView.AllowUserToAddRows = false;
			this.dataGridView.AllowUserToDeleteRows = false;
			this.dataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dataGridView.Location = new System.Drawing.Point(0, 0);
			this.dataGridView.Name = "dataGridView";
			this.dataGridView.ReadOnly = true;
			this.dataGridView.Size = new System.Drawing.Size(629, 315);
			this.dataGridView.TabIndex = 3;
			// 
			// panelPlayers
			// 
			this.panelPlayers.Dock = System.Windows.Forms.DockStyle.Top;
			this.panelPlayers.Location = new System.Drawing.Point(0, 0);
			this.panelPlayers.Name = "panelPlayers";
			this.panelPlayers.Size = new System.Drawing.Size(629, 516);
			this.panelPlayers.TabIndex = 0;
			// 
			// listBoxStatus
			// 
			this.listBoxStatus.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBoxStatus.FormattingEnabled = true;
			this.listBoxStatus.HorizontalScrollbar = true;
			this.listBoxStatus.Location = new System.Drawing.Point(0, 561);
			this.listBoxStatus.Name = "listBoxStatus";
			this.listBoxStatus.Size = new System.Drawing.Size(421, 270);
			this.listBoxStatus.TabIndex = 1;
			// 
			// toolStripMainMenu
			// 
			this.toolStripMainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonJoinOpened,
            this.toolStripButtonJoinClosed,
            this.toolStripSeparator2,
            this.toolStripButtonPlay,
            this.toolStripButtonStep,
            this.toolStripButtonPause,
            this.toolStripButtonStop,
            this.toolStripSeparator1,
            this.toolStripButtonSpeed,
            this.toolStripButtonTimeout,
            this.toolStripButtonMute});
			this.toolStripMainMenu.Location = new System.Drawing.Point(0, 0);
			this.toolStripMainMenu.Name = "toolStripMainMenu";
			this.toolStripMainMenu.Size = new System.Drawing.Size(1050, 25);
			this.toolStripMainMenu.TabIndex = 1;
			this.toolStripMainMenu.Text = "toolStrip1";
			// 
			// toolStripButtonJoinOpened
			// 
			this.toolStripButtonJoinOpened.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonJoinOpened.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonJoinOpened.Image")));
			this.toolStripButtonJoinOpened.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonJoinOpened.Name = "toolStripButtonJoinOpened";
			this.toolStripButtonJoinOpened.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonJoinOpened.Text = "join";
			this.toolStripButtonJoinOpened.Click += new System.EventHandler(this.toolStripButtonJoin_Click);
			// 
			// toolStripButtonJoinClosed
			// 
			this.toolStripButtonJoinClosed.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonJoinClosed.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonJoinClosed.Image")));
			this.toolStripButtonJoinClosed.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonJoinClosed.Name = "toolStripButtonJoinClosed";
			this.toolStripButtonJoinClosed.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonJoinClosed.Text = "lock";
			this.toolStripButtonJoinClosed.Click += new System.EventHandler(this.toolStripButtonClosed_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// toolStripButtonPlay
			// 
			this.toolStripButtonPlay.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonPlay.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonPlay.Image")));
			this.toolStripButtonPlay.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonPlay.Name = "toolStripButtonPlay";
			this.toolStripButtonPlay.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonPlay.Text = "Play";
			this.toolStripButtonPlay.Click += new System.EventHandler(this.Play_Click);
			// 
			// toolStripButtonStep
			// 
			this.toolStripButtonStep.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonStep.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonStep.Image")));
			this.toolStripButtonStep.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonStep.Name = "toolStripButtonStep";
			this.toolStripButtonStep.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonStep.Text = "step";
			this.toolStripButtonStep.Click += new System.EventHandler(this.toolStripButtonStep_Click);
			// 
			// toolStripButtonPause
			// 
			this.toolStripButtonPause.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonPause.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonPause.Image")));
			this.toolStripButtonPause.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonPause.Name = "toolStripButtonPause";
			this.toolStripButtonPause.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonPause.Text = "Pause";
			this.toolStripButtonPause.Click += new System.EventHandler(this.Pause_Click);
			// 
			// toolStripButtonStop
			// 
			this.toolStripButtonStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonStop.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonStop.Image")));
			this.toolStripButtonStop.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonStop.Name = "toolStripButtonStop";
			this.toolStripButtonStop.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonStop.Text = "Stop";
			this.toolStripButtonStop.Click += new System.EventHandler(this.Stop_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// toolStripButtonSpeed
			// 
			this.toolStripButtonSpeed.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonSpeed.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonSpeed.Image")));
			this.toolStripButtonSpeed.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonSpeed.Name = "toolStripButtonSpeed";
			this.toolStripButtonSpeed.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonSpeed.Text = "speed";
			this.toolStripButtonSpeed.Click += new System.EventHandler(this.toolStripButtonSpeed_Click);
			// 
			// toolStripButtonTimeout
			// 
			this.toolStripButtonTimeout.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonTimeout.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonTimeout.Image")));
			this.toolStripButtonTimeout.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonTimeout.Name = "toolStripButtonTimeout";
			this.toolStripButtonTimeout.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonTimeout.Text = "client timeout";
			this.toolStripButtonTimeout.Click += new System.EventHandler(this.toolStripButtonTimeout_Click);
			// 
			// toolStripButtonMute
			// 
			this.toolStripButtonMute.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonMute.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonMute.Image")));
			this.toolStripButtonMute.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonMute.Name = "toolStripButtonMute";
			this.toolStripButtonMute.Size = new System.Drawing.Size(23, 22);
			this.toolStripButtonMute.Text = "mute";
			this.toolStripButtonMute.Click += new System.EventHandler(this.toolStripButtonMute_Click);
			// 
			// panelLeft
			// 
			this.panelLeft.Controls.Add(this.listBoxStatus);
			this.panelLeft.Controls.Add(this.mapDisplay);
			this.panelLeft.Dock = System.Windows.Forms.DockStyle.Left;
			this.panelLeft.Location = new System.Drawing.Point(0, 25);
			this.panelLeft.Name = "panelLeft";
			this.panelLeft.Size = new System.Drawing.Size(421, 831);
			this.panelLeft.TabIndex = 3;
			// 
			// mapDisplay
			// 
			this.mapDisplay.AutoScroll = true;
			this.mapDisplay.Dock = System.Windows.Forms.DockStyle.Top;
			this.mapDisplay.Location = new System.Drawing.Point(0, 0);
			this.mapDisplay.Name = "mapDisplay";
			this.mapDisplay.Size = new System.Drawing.Size(421, 561);
			this.mapDisplay.TabIndex = 2;
			// 
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1050, 856);
			this.Controls.Add(this.panelRight);
			this.Controls.Add(this.panelLeft);
			this.Controls.Add(this.toolStripMainMenu);
			this.DoubleBuffered = true;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "MainWindow";
			this.Text = "RoboRally";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.GameDisplay_FormClosing);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWindow_FormClosed);
			this.Load += new System.EventHandler(this.MainWindow_Load);
			this.panelRight.ResumeLayout(false);
			this.panelBottom.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
			this.toolStripMainMenu.ResumeLayout(false);
			this.toolStripMainMenu.PerformLayout();
			this.panelLeft.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel panelRight;
		private System.Windows.Forms.ToolStrip toolStripMainMenu;
		private System.Windows.Forms.ToolStripButton toolStripButtonPlay;
		private System.Windows.Forms.ToolStripButton toolStripButtonPause;
		private System.Windows.Forms.ToolStripButton toolStripButtonStop;
		private MapDisplay mapDisplay;
		private System.Windows.Forms.Panel panelPlayers;
		private System.Windows.Forms.ListBox listBoxStatus;
		private System.Windows.Forms.Panel panelBottom;
		private System.Windows.Forms.ToolStripButton toolStripButtonJoinOpened;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton toolStripButtonSpeed;
		private System.Windows.Forms.ToolStripButton toolStripButtonJoinClosed;
		private System.Windows.Forms.ToolStripButton toolStripButtonStep;
		private System.Windows.Forms.Panel panelLeft;
		private System.Windows.Forms.DataGridView dataGridView;
		private System.Windows.Forms.ToolStripButton toolStripButtonTimeout;
		private System.Windows.Forms.ToolStripButton toolStripButtonMute;
	}
}