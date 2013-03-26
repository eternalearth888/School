using System.Drawing;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A player's robot.
	/// </summary>
	public class Robot : CombatUnit
	{
		/// <summary>
		/// Create a new Robot object.
		/// </summary>
		/// <param name="location">The unit is at this location on the map.</param>
		/// <param name="bitmap">The bitmaps for this robot facing. Index using DIRECTION.</param>
		public Robot(BoardLocation location, Bitmap bitmap) : base(location)
		{
			Bitmaps = new Bitmap[4];
			Bitmaps[(int)MapSquare.DIRECTION.NORTH] = bitmap;
			Bitmaps[(int)MapSquare.DIRECTION.EAST] = new Bitmap(bitmap);
			Bitmaps[(int)MapSquare.DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate90FlipNone);
			Bitmaps[(int)MapSquare.DIRECTION.SOUTH] = new Bitmap(bitmap);
			Bitmaps[(int)MapSquare.DIRECTION.SOUTH].RotateFlip(RotateFlipType.Rotate180FlipNone);
			Bitmaps[(int)MapSquare.DIRECTION.WEST] = new Bitmap(bitmap);
			Bitmaps[(int)MapSquare.DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate270FlipNone);
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public Robot(Robot src) : base(src)
		{
		}

		/// <summary>
		/// The bitmaps for this robot facing. Index using DIRECTION. This is used by the engine and will be null when
		/// this object is passed to a player.
		/// </summary>
		public Bitmap [] Bitmaps { get; private set; }

		public XElement XML
		{
			get
			{
				XElement xmlRobot = new XElement("robot");
				xmlRobot.Add(Attributes);
				return xmlRobot;
			}
		}
	}
}
