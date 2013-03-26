// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Drawing;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A single map square.
	/// </summary>
	public class MapSquare : ISprite
	{
		private Bitmap bitmap;

		// index is DIRECTION - NESW
		private static readonly Bitmap[] walls;
		private static readonly Bitmap[] lasers;

		private static readonly Bitmap[][] conv_straight;
		private static readonly Bitmap[][] conv_clockwise;
		private static readonly Bitmap[][] conv_counterclockwise;

		/// <summary>
		/// A lot of the sprites are created by rotating and/or flipping the sprites in the resources. Done here.
		/// </summary>
		static MapSquare()
		{
			// conveyor belts - straight
			conv_straight = new Bitmap[3][];
			conv_straight[1] = InitBitmaps(Sprites.cnv_1_east);
			conv_straight[1][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate270FlipNone);
			conv_straight[1][(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.Rotate90FlipNone);
			conv_straight[1][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate180FlipNone);

			conv_straight[2] = InitBitmaps(Sprites.cnv_2_east);
			conv_straight[2][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate270FlipNone);
			conv_straight[2][(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.Rotate90FlipNone);
			conv_straight[2][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate180FlipNone);

			// conveyor belts - right turn
			conv_clockwise = new Bitmap[3][];
			conv_clockwise[1] = InitBitmaps(Sprites.cnv_1_east_south);
			conv_clockwise[1][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate180FlipNone);
			conv_clockwise[1][(int)DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate270FlipNone);
			conv_clockwise[1][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate90FlipNone);

			conv_clockwise[2] = InitBitmaps(Sprites.cnv_2_east_south);
			conv_clockwise[2][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate180FlipNone);
			conv_clockwise[2][(int)DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate270FlipNone);
			conv_clockwise[2][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate90FlipNone);

			// conveyor belts - left turn
			conv_counterclockwise = new Bitmap[3][];
			conv_counterclockwise[1] = InitBitmaps(Sprites.cnv_1_east_south);
			conv_counterclockwise[1][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate180FlipX);
			conv_counterclockwise[1][(int)DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate90FlipX);
			conv_counterclockwise[1][(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.RotateNoneFlipX);
			conv_counterclockwise[1][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate270FlipX);

			conv_counterclockwise[2] = InitBitmaps(Sprites.cnv_2_east_south);
			conv_counterclockwise[2][(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate180FlipX);
			conv_counterclockwise[2][(int)DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate90FlipX);
			conv_counterclockwise[2][(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.RotateNoneFlipX);
			conv_counterclockwise[2][(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate270FlipX);

			// walls
			walls = InitBitmaps(Sprites.wall);
			walls[(int)DIRECTION.EAST].RotateFlip(RotateFlipType.Rotate90FlipNone);
			walls[(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.Rotate180FlipNone);
			walls[(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate270FlipNone);

			// lasers
			lasers = InitBitmaps(Sprites.laser);
			lasers[(int)DIRECTION.NORTH].RotateFlip(RotateFlipType.Rotate270FlipNone);
			lasers[(int)DIRECTION.SOUTH].RotateFlip(RotateFlipType.Rotate90FlipNone);
			lasers[(int)DIRECTION.WEST].RotateFlip(RotateFlipType.Rotate180FlipNone);
		}

		
		/// <summary>
		/// The direction a robot or laser is facing. ALso used for direction a conveyor is running (exit for a turn).
		/// </summary>
		public enum DIRECTION
		{
			/// <summary>
			/// Facing North and can fire on units above.
			/// </summary>
			NORTH = 0,
			/// <summary>
			/// Facing East and can fire on units to the right.
			/// </summary>
			EAST = 1,
			/// <summary>
			/// Facing South and can fire on units below.
			/// </summary>
			SOUTH = 2,
			/// <summary>
			/// Facing West and can fire on units to the left.
			/// </summary>
			WEST = 3
		};

		/// <summary>
		/// Which side(s) of the square have a wall. A square can have multiple walls.
		/// </summary>
		[Flags]
		public enum SIDE
		{
			/// <summary>
			/// No walls.
			/// </summary>
			NONE = 0,
			/// <summary>
			/// A wall on the North (top) side.
			/// </summary>
			NORTH = 0x01,
			/// <summary>
			/// A wall on the East (right) side.
			/// </summary>
			EAST = 0x02,
			/// <summary>
			/// A wall on the South (bottom) side.
			/// </summary>
			SOUTH = 0x04,
			/// <summary>
			/// A wall on the West (left) side.
			/// </summary>
			WEST = 0x08
		}

		/// <summary>
		/// What type of square it is.
		/// </summary>
		public enum TYPE
		{
			/// <summary>
			/// Normal - nothing on it.
			/// </summary>
			NORMAL,
			/// <summary>
			/// Has a conveyor belt on it.
			/// </summary>
			CONVEYOR_BELT,
			/// <summary>
			/// Is a gear that rotates clockwise.
			/// </summary>
			ROTATE_CLOCKWISE,
			/// <summary>
			/// Is a gear that rotates counter-clockwise.
			/// </summary>
			ROTATE_COUNTERCLOCKWISE,
			/// <summary>
			/// Is a repair square.
			/// </summary>
			REPAIR,
			/// <summary>
			/// Is a flag.
			/// </summary>
			FLAG,
			/// <summary>
			/// It is a pit.
			/// </summary>
			PIT
		}

		/// <summary>
		/// Create a map square set to NORMAL.
		/// </summary>
		protected MapSquare()
		{
			Type = TYPE.NORMAL;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this object.</param>
		public MapSquare(MapSquare src)
		{
			Type = src.Type;
			Walls = src.Walls;
			Conveyor = src.Conveyor == null ? null : new Conveyor(src.Conveyor);
			Laser = src.Laser == null ? null : new Laser(src.Laser);
			Flag = src.Flag;
		}

		/// <summary>
		/// The type of square.
		/// </summary>
		public TYPE Type { get; protected set; }

		/// <summary>
		/// What sides (if any) have walls.
		/// </summary>
		public SIDE Walls { get; protected set; }

		/// <summary>
		/// The conveyor belt on this square. null if no conveyor.
		/// </summary>
		public Conveyor Conveyor { get; protected set; }

		/// <summary>
		/// The laser on this square. null if no laser.
		/// </summary>
		public Laser Laser { get; protected set; }

		/// <summary>
		/// The flag number (1..3) on this square. 0 if no flag.
		/// </summary>
		public int Flag { get; protected set; }

		public XElement GetXML(int x, int y)
		{
			XElement xmlSquare = new XElement("square", new XAttribute("x", x), new XAttribute("y", y),
						new XAttribute("type", Type), new XAttribute("walls", Walls), new XAttribute("flag", Flag));
			if (Conveyor != null)
				xmlSquare.Add(Conveyor.XML);
			if (Laser != null)
				xmlSquare.Add(Laser.XML);
			return xmlSquare;
		}

		private static Bitmap[] InitBitmaps(Bitmap bmp)
		{
			Bitmap [] arrBitmaps = new Bitmap[4];
			for (int ind = 0; ind < 4; ind++ )
				arrBitmaps[ind] = new Bitmap(bmp);
			return arrBitmaps;
		}

		/// <summary>
		/// Create a map square of the requested type. No Conveyor or Laser.
		/// </summary>
		/// <param name="type">The square type.</param>
		public MapSquare(TYPE type)
		{
			Type = type;
			Walls = 0;
			Conveyor = null;
			Laser = null;
			Flag = 0;

			BuildSpriteBitmap();
		}

		/// <summary>
		/// Create a map square with walls. Type = normal, no Conveyor or Laser.
		/// </summary>
		/// <param name="walls">The map walls.</param>
		public MapSquare(SIDE walls)
		{
			Type = TYPE.NORMAL;
			Walls = walls;
			Conveyor = null;
			Laser = null;
			Flag = 0;

			BuildSpriteBitmap();
		}

		/// <summary>
		/// Create a map square of the requested type with walls.
		/// </summary>
		/// <param name="type">The square type.</param>
		/// <param name="walls">The map walls.</param>
		public MapSquare(TYPE type, SIDE walls)
		{
			Type = type;
			Walls = walls;
			Conveyor = null;
			Laser = null;
			Flag = 0;

			BuildSpriteBitmap();
		}

		/// <summary>
		/// Create a map square with a conveyor belt. No walls or laser.
		/// </summary>
		/// <param name="conveyor">The conveyor belt for this square.</param>
		public MapSquare(Conveyor conveyor)
		{
			Type = TYPE.CONVEYOR_BELT;
			Walls = 0;
			Conveyor = conveyor;
			Laser = null;
			Flag = 0;

			BuildSpriteBitmap();
		}

		/// <summary>
		/// Create a map square with a laser and wall.
		/// </summary>
		/// <param name="laser">The laser for the square.</param>
		/// <param name="walls">The wall(s) for the laser.</param>
		public MapSquare(Laser laser, SIDE walls)
		{
			Type = TYPE.NORMAL;
			Walls = walls;
			Conveyor = null;
			Laser = laser;
			Flag = 0;

			BuildSpriteBitmap();
		}

		/// <summary>
		/// Create a map square with a flag.
		/// </summary>
		/// <param name="flag">The flag number.</param>
		public MapSquare(int flag)
		{
			Type = TYPE.FLAG;
			Walls = 0;
			Conveyor = null;
			Laser = null;
			Flag = flag;

			BuildSpriteBitmap();
		}

		private void BuildSpriteBitmap()
		{
			switch (Type)
			{
				case TYPE.NORMAL:
					bitmap = Sprites.floor;
					break;
				case TYPE.REPAIR:
					bitmap = Sprites.repair;
					break;
				case TYPE.ROTATE_CLOCKWISE:
					bitmap = Sprites.rotate_clock;
					break;
				case TYPE.ROTATE_COUNTERCLOCKWISE:
					bitmap = Sprites.rotate_counter;
					break;

				case TYPE.FLAG:
					bitmap = Sprites.floor_flag;
					break;
				case TYPE.PIT:
					bitmap = Sprites.p01234;
					break;

				case TYPE.CONVEYOR_BELT:
					Bitmap[] arrBmp;
					if (Conveyor.Entry == SIDE.NONE)
						arrBmp = conv_straight[Conveyor.Speed];
					else
					{
						switch (Conveyor.Direction)
						{
							case DIRECTION.NORTH:
								arrBmp = (Conveyor.Entry & SIDE.WEST) != 0
								         	? conv_clockwise[Conveyor.Speed]
								         	: conv_counterclockwise[Conveyor.Speed];
								break;
							case DIRECTION.EAST:
								arrBmp = (Conveyor.Entry & SIDE.NORTH) != 0
								         	? conv_clockwise[Conveyor.Speed]
								         	: conv_counterclockwise[Conveyor.Speed];
								break;
							case DIRECTION.SOUTH:
								arrBmp = (Conveyor.Entry & SIDE.EAST) != 0
								         	? conv_clockwise[Conveyor.Speed]
								         	: conv_counterclockwise[Conveyor.Speed];
								break;
							case DIRECTION.WEST:
								arrBmp = (Conveyor.Entry & SIDE.SOUTH) != 0
								         	? conv_clockwise[Conveyor.Speed]
								         	: conv_counterclockwise[Conveyor.Speed];
								break;
							default:
								throw new ApplicationException("unknown direction " + Conveyor.Direction);
						}
					}

					bitmap = arrBmp[(int) Conveyor.Direction];
					break;

				default:
					Trap.trap();
					bitmap = Sprites.floor;
					break;
			}

			// walls
			bool ownBitmap = false;
			if (Walls != SIDE.NONE)
			{
				bitmap = new Bitmap(bitmap);
				ownBitmap = true;
				using (Graphics g = Graphics.FromImage(bitmap))
				{
					if ((Walls & SIDE.NORTH) != 0)
						g.DrawImage(walls[(int) DIRECTION.NORTH], 0, 0);
					if ((Walls & SIDE.EAST) != 0)
						g.DrawImage(walls[(int)DIRECTION.EAST], bitmap.Width - walls[(int)DIRECTION.EAST].Width, 0);
					if ((Walls & SIDE.SOUTH) != 0)
						g.DrawImage(walls[(int)DIRECTION.SOUTH], 0, bitmap.Height - walls[(int)DIRECTION.SOUTH].Height);
					if ((Walls & SIDE.WEST) != 0)
						g.DrawImage(walls[(int)DIRECTION.WEST], 0, 0);
				}
			}

			// laser
			if (Laser != null)
			{
				if (!ownBitmap)
					bitmap = new Bitmap(bitmap);
				using (Graphics g = Graphics.FromImage(bitmap))
				{
					Bitmap bmpLaser = lasers[(int) Laser.Location.Direction];
					switch (Laser.Location.Direction)
					{
						case DIRECTION.NORTH:
							g.DrawImage(bmpLaser, (bitmap.Width - bmpLaser.Width) / 2, bitmap.Height - bmpLaser.Height);
							break;
						case DIRECTION.EAST:
							g.DrawImage(bmpLaser, 0, (bitmap.Height - bmpLaser.Height) / 2);
							break;
						case DIRECTION.SOUTH:
							g.DrawImage(bmpLaser, (bitmap.Width - bmpLaser.Width) / 2, 0);
							break;
						case DIRECTION.WEST:
							g.DrawImage(bmpLaser, bitmap.Width - bmpLaser.Width, (bitmap.Height - bmpLaser.Height) / 2);
							break;
					}
				}
			}
		}

		/// <summary>
		/// Called once each tick (used for animation).
		/// </summary>
		/// <returns>true to kill this sprite, false to keep it alive.</returns>
		public bool IncreaseTick()
		{
			return false;
		}

		/// <summary>
		/// The bitmap for this sprite. This will change on ticks for animated sprites.
		/// </summary>
		public Image SpriteBitmap
		{
			get
			{
				return bitmap;
			}
		}
	}
}
