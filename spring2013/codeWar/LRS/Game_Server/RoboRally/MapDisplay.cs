// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using RoboRallyNet.game_engine;

namespace RoboRallyNet
{
	/// <summary>
	/// The map window.
	/// </summary>
	public partial class MapDisplay : UserControl
	{
		/// <summary>The pixel size of each map square.</summary>
		private const int SQUARE_SIZE = 35;

		/// <summary>
		/// Create the map window.
		/// </summary>
		public MapDisplay()
		{
			InitializeComponent();
		}

		private Framework GameFramework
		{
			get
			{
				Control ctrl = Parent;
				while (ctrl != null)
				{
					MainWindow wnd = ctrl as MainWindow;
					if (wnd != null)
						return wnd.GameFramework;
					ctrl = ctrl.Parent;
				}
				return null;
			}
		} 

		/// <summary>
		/// Paint the window.
		/// </summary>
		private void MapDisplay_Paint(object sender, PaintEventArgs pea)
		{

			// not parent in design mode
			Framework framework = GameFramework;
			if (framework == null)
				return;

			GameMap map = framework.GameEngine.MainMap;
			for (int x=0; x<map.Squares.Length; x++)
				for (int y = 0; y < map.Squares[x].Length; y++)
				{
					MapSquare square = map.Squares[x][y];
					pea.Graphics.DrawImage(square.SpriteBitmap, x * SQUARE_SIZE, y * SQUARE_SIZE);
				}

			// laser beams - they go under everything.
			if (framework.laserBeams.Count > 0)
				using (Pen pen = new Pen(Color.Red, 2))
					foreach (LaserBeam beam in framework.laserBeams)
					{
						// convert to map coordinates - middle of each square.
						Point start = new Point(beam.PositionStart.X*SQUARE_SIZE + SQUARE_SIZE/2, beam.PositionStart.Y*SQUARE_SIZE + SQUARE_SIZE/2);
						Point end = new Point(beam.PositionEnd.X*SQUARE_SIZE + SQUARE_SIZE/2, beam.PositionEnd.Y*SQUARE_SIZE + SQUARE_SIZE/2);
						pea.Graphics.DrawLine(pen, start, end);
					}

			// flags
			pea.Graphics.DrawImage(Sprites.flag_green, 5 * SQUARE_SIZE + 8, 4 * SQUARE_SIZE - 8);
			pea.Graphics.DrawImage(Sprites.flag_blue, 10 * SQUARE_SIZE + 8, 11 * SQUARE_SIZE - 8);
			pea.Graphics.DrawImage(Sprites.flag_purple, 1 * SQUARE_SIZE + 8, 6 * SQUARE_SIZE - 8);

			// get all alive robots
			List<Robot> robots = (from player in framework.GameEngine.Players where (player.IsVisible) && (player.Robot != null) select player.Robot).ToList();

			// robots
			foreach (Robot robotOn in robots)
			{
				Bitmap bmpRobot = robotOn.Bitmaps[(int)robotOn.Location.Direction];
				pea.Graphics.DrawImage(bmpRobot, robotOn.Location.MapPosition.X * SQUARE_SIZE + (SQUARE_SIZE - bmpRobot.Width) / 2,
					robotOn.Location.MapPosition.Y * SQUARE_SIZE + (SQUARE_SIZE - bmpRobot.Height) / 2);
			}

			foreach (Sprite spriteOn in framework.sprites)
			{
				Image bitmap = spriteOn.SpriteBitmap;
				pea.Graphics.DrawImage(bitmap, spriteOn.Location.X * SQUARE_SIZE + (SQUARE_SIZE - bitmap.Width) / 2, 
										spriteOn.Location.Y * SQUARE_SIZE + (SQUARE_SIZE - bitmap.Height) / 2);
			}
		}
	}
}
