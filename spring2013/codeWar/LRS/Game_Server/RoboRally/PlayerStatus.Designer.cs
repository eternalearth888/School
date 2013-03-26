namespace RoboRallyNet
{
	partial class PlayerStatus
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlayerStatus));
			this.pictureBoxAvatar = new System.Windows.Forms.PictureBox();
			this.labelScore = new System.Windows.Forms.Label();
			this.labelName = new System.Windows.Forms.Label();
			this.pictureBoxRobot = new System.Windows.Forms.PictureBox();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxAvatar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxRobot)).BeginInit();
			this.SuspendLayout();
			// 
			// pictureBoxAvatar
			// 
			this.pictureBoxAvatar.Image = ((System.Drawing.Image)(resources.GetObject("pictureBoxAvatar.Image")));
			this.pictureBoxAvatar.Location = new System.Drawing.Point(4, 4);
			this.pictureBoxAvatar.Name = "pictureBoxAvatar";
			this.pictureBoxAvatar.Size = new System.Drawing.Size(32, 32);
			this.pictureBoxAvatar.TabIndex = 0;
			this.pictureBoxAvatar.TabStop = false;
			// 
			// labelScore
			// 
			this.labelScore.AutoSize = true;
			this.labelScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelScore.Location = new System.Drawing.Point(65, 4);
			this.labelScore.Name = "labelScore";
			this.labelScore.Size = new System.Drawing.Size(48, 26);
			this.labelScore.TabIndex = 1;
			this.labelScore.Text = "000";
			// 
			// labelName
			// 
			this.labelName.AutoEllipsis = true;
			this.labelName.Location = new System.Drawing.Point(4, 44);
			this.labelName.Name = "labelName";
			this.labelName.Size = new System.Drawing.Size(303, 13);
			this.labelName.TabIndex = 3;
			this.labelName.Text = "David Thielen";
			// 
			// pictureBoxRobot
			// 
			this.pictureBoxRobot.Location = new System.Drawing.Point(40, 4);
			this.pictureBoxRobot.Name = "pictureBoxRobot";
			this.pictureBoxRobot.Size = new System.Drawing.Size(23, 23);
			this.pictureBoxRobot.TabIndex = 4;
			this.pictureBoxRobot.TabStop = false;
			// 
			// PlayerStatus
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.pictureBoxRobot);
			this.Controls.Add(this.labelName);
			this.Controls.Add(this.labelScore);
			this.Controls.Add(this.pictureBoxAvatar);
			this.DoubleBuffered = true;
			this.Name = "PlayerStatus";
			this.Size = new System.Drawing.Size(313, 129);
			this.Load += new System.EventHandler(this.PlayerStatus_Load);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.PlayerStatus_Paint);
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxAvatar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxRobot)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox pictureBoxAvatar;
		private System.Windows.Forms.Label labelScore;
		private System.Windows.Forms.Label labelName;
		private System.Windows.Forms.PictureBox pictureBoxRobot;
	}
}
