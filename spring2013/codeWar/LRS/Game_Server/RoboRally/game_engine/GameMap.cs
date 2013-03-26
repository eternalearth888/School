using System.Collections.Generic;
using System.Drawing;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// The game map.
	/// </summary>
	public class GameMap
	{
		// the map size.
		private const int MAP_SQUARE_HEIGHT = 16;
		private const int MAP_SQUARE_WIDTH = 12;

		/// <summary>
		/// Create a map with no squares.
		/// </summary>
		protected GameMap()
		{
			Lasers = new List<Laser>();
		}

		/// <summary>
		/// The lasers on the map.
		/// </summary>
		public List<Laser> Lasers { get; private set; }

		/// <summary>
		/// The width of the map. Units are squares.
		/// </summary>
		public int Width
		{
			get { return Squares.Length; }
		}

		/// <summary>
		/// The height of the map. Units are squares.
		/// </summary>
		public int Height
		{
			get { return Squares[0].Length; }
		}

		/// <summary>
		/// The map squares. This is in the format [x][y].
		/// </summary>
		public MapSquare[][] Squares { get; protected set; }

		/// <summary>
		/// Location (map squares) of the flags in order.
		/// </summary>
		public Point[] Flags { get; protected set; }

		/// <summary>
		/// Get a specific map square.
		/// </summary>
		/// <param name="location">The x, y point for the square desired.</param>
		/// <returns>The requested square.</returns>
		public MapSquare GetSquare(Point location)
		{
			return Squares[location.X][location.Y];
		}

		/// <summary>
		/// Get a specific map square.
		/// </summary>
		/// <param name="x">The x point for the square desired.</param>
		/// <param name="y">The y point for the square desired.</param>
		/// <returns>The requested square.</returns>
		public MapSquare GetSquare(int x, int y)
		{
			return Squares[x][y];
		}

		/// <summary>
		/// Create the XML of the map that we send to players.
		/// </summary>
		public XElement XML
		{
			get
			{
				XElement xmlMap = new XElement("map", new XAttribute("width", Width), new XAttribute("height", Height));

				for (int x = 0; x < MAP_SQUARE_WIDTH; x++)
					for (int y = 0; y < MAP_SQUARE_HEIGHT; y++)
						xmlMap.Add(GetSquare(x, y).GetXML(x, y));

				return xmlMap;
			}
		}

		/// <summary>
		/// Create the map.
		/// </summary>
		/// <returns></returns>
		public static GameMap CreateMap()
		{
			// build map - all standard tiles
			GameMap map = new GameMap { Squares = new MapSquare[MAP_SQUARE_WIDTH][] };
			for (int x = 0; x < MAP_SQUARE_WIDTH; x++)
			{
				map.Squares[x] = new MapSquare[MAP_SQUARE_HEIGHT];
				for (int y=0; y<MAP_SQUARE_HEIGHT; y++)
					map.Squares[x][y] = new MapSquare(MapSquare.TYPE.NORMAL);
			}

			// walls
			map.Squares[2][0] = new MapSquare(MapSquare.SIDE.NORTH);
			map.Squares[4][0] = new MapSquare(MapSquare.SIDE.NORTH);
			map.Squares[7][0] = new MapSquare(MapSquare.SIDE.NORTH);
			map.Squares[9][0] = new MapSquare(MapSquare.SIDE.NORTH);

			map.Squares[0][2] = new MapSquare(MapSquare.SIDE.WEST);
			// pit - map.Squares[3][2] = new MapSquare(MapSquare.SIDE.SOUTH);
			map.Squares[11][2] = new MapSquare(MapSquare.SIDE.EAST);

			map.Squares[5][3] = new MapSquare(MapSquare.SIDE.WEST);
			// laser - map.Squares[6][3] = new MapSquareInternal(MapSquare.SIDE.EAST);

			map.Squares[0][4] = new MapSquare(MapSquare.SIDE.WEST);
			map.Squares[11][4] = new MapSquare(MapSquare.SIDE.EAST);

			// laser - map.Squares[8][5] = new MapSquareInternal(MapSquare.SIDE.NORTH);

			// laser - map.Squares[3][6] = new MapSquareInternal(MapSquare.SIDE.SOUTH);

			map.Squares[0][7] = new MapSquare(MapSquare.SIDE.WEST);
			map.Squares[11][7] = new MapSquare(MapSquare.SIDE.EAST);

			// laser - map.Squares[5][8] = new MapSquareInternal(MapSquare.SIDE.WEST);
			map.Squares[6][8] = new MapSquare(MapSquare.SIDE.EAST);

			map.Squares[0][9] = new MapSquare(MapSquare.SIDE.WEST);
			// pit - map.Squares[8][9] = new MapSquare(MapSquare.SIDE.NORTH);
			map.Squares[11][9] = new MapSquare(MapSquare.SIDE.EAST);

			map.Squares[2][11] = new MapSquare(MapSquare.SIDE.SOUTH);
			map.Squares[4][11] = new MapSquare(MapSquare.SIDE.SOUTH);
			map.Squares[7][11] = new MapSquare(MapSquare.SIDE.SOUTH);
			map.Squares[9][11] = new MapSquare(MapSquare.SIDE.SOUTH);

			map.Squares[2][12] = new MapSquare(MapSquare.SIDE.NORTH);
			map.Squares[4][12] = new MapSquare(MapSquare.SIDE.NORTH | MapSquare.SIDE.WEST);
			map.Squares[7][12] = new MapSquare(MapSquare.SIDE.NORTH | MapSquare.SIDE.EAST);
			map.Squares[9][12] = new MapSquare(MapSquare.SIDE.NORTH);

			map.Squares[1][13] = new MapSquare(MapSquare.SIDE.WEST);
			map.Squares[2][13] = new MapSquare(MapSquare.SIDE.WEST);
			map.Squares[9][13] = new MapSquare(MapSquare.SIDE.EAST);
			map.Squares[10][13] = new MapSquare(MapSquare.SIDE.EAST);

			map.Squares[6][14] = new MapSquare(MapSquare.SIDE.WEST);

			map.Squares[6][15] = new MapSquare(MapSquare.SIDE.WEST);

			// 4 square conveyor belts
			map.Squares[1][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NORTH));
			map.Squares[2][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[3][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[4][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.EAST));
			map.Squares[4][2] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[4][3] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[4][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.SOUTH));
			map.Squares[3][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[2][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[1][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.WEST));
			map.Squares[1][3] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));
			map.Squares[1][2] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));

			map.Squares[7][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NORTH));
			map.Squares[8][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[9][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[10][1] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.EAST));
			map.Squares[10][2] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[10][3] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[10][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.SOUTH));
			map.Squares[9][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[8][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[7][4] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.WEST));
			map.Squares[7][3] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));
			map.Squares[7][2] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));

			map.Squares[1][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NORTH));
			map.Squares[2][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[3][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[4][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.EAST));
			map.Squares[4][8] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[4][9] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[4][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.SOUTH));
			map.Squares[3][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[2][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[1][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.WEST));
			map.Squares[1][9] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));
			map.Squares[1][8] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));

			map.Squares[7][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NORTH));
			map.Squares[8][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[9][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[10][7] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.EAST));
			map.Squares[10][8] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[10][9] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NONE));
			map.Squares[10][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.SOUTH));
			map.Squares[9][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[8][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[7][10] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.WEST));
			map.Squares[7][9] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));
			map.Squares[7][8] = new MapSquare(new Conveyor(2, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.NONE));

			// 2 start conveyor belts
			map.Squares[0][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[1][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[2][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.EAST));
			map.Squares[2][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.EAST, MapSquare.SIDE.SOUTH));
			map.Squares[3][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));
			map.Squares[4][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.EAST, MapSquare.SIDE.NONE));

			map.Squares[7][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[8][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[9][15] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.WEST, MapSquare.SIDE.SOUTH));
			map.Squares[9][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.WEST));
			map.Squares[10][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));
			map.Squares[11][14] = new MapSquare(new Conveyor(1, MapSquare.DIRECTION.WEST, MapSquare.SIDE.NONE));

			// rotators
			map.Squares[2][2] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[8][2] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[3][3] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[9][3] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);

			map.Squares[2][8] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[8][8] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[3][9] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);
			map.Squares[9][9] = new MapSquare(MapSquare.TYPE.ROTATE_CLOCKWISE);

			map.Squares[5][2] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[6][4] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[4][5] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[9][5] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);

			map.Squares[2][6] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[7][6] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[5][7] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);
			map.Squares[6][9] = new MapSquare(MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE);

			// lasers
			map.Lasers.Add(new Laser(new BoardLocation(new Point(6, 3), MapSquare.DIRECTION.WEST), 2));
			map.Lasers.Add(new Laser(new BoardLocation(new Point(5, 8), MapSquare.DIRECTION.EAST), 2));
			map.Lasers.Add(new Laser(new BoardLocation(new Point(3, 6), MapSquare.DIRECTION.NORTH), 4));
			map.Lasers.Add(new Laser(new BoardLocation(new Point(8, 5), MapSquare.DIRECTION.SOUTH), 4));
			map.Squares[6][3] = new MapSquare(map.Lasers[0], MapSquare.SIDE.EAST);
			map.Squares[5][8] = new MapSquare(map.Lasers[1], MapSquare.SIDE.WEST);
			map.Squares[3][6] = new MapSquare(map.Lasers[2], MapSquare.SIDE.SOUTH);
			map.Squares[8][5] = new MapSquare(map.Lasers[3], MapSquare.SIDE.NORTH);

			// repair
			map.Squares[2][3] = new MapSquare(MapSquare.TYPE.REPAIR);
			map.Squares[8][3] = new MapSquare(MapSquare.TYPE.REPAIR);
			map.Squares[3][8] = new MapSquare(MapSquare.TYPE.REPAIR);
			map.Squares[9][8] = new MapSquare(MapSquare.TYPE.REPAIR);

			// pits
			map.Squares[3][2] = new MapSquare(MapSquare.TYPE.PIT, MapSquare.SIDE.SOUTH);
			map.Squares[9][2] = new MapSquare(MapSquare.TYPE.PIT);
			map.Squares[2][9] = new MapSquare(MapSquare.TYPE.PIT);
			map.Squares[8][9] = new MapSquare(MapSquare.TYPE.PIT, MapSquare.SIDE.NORTH);

			// flags
			map.Squares[5][4] = new MapSquare(1);
			map.Squares[10][11] = new MapSquare(2);
			map.Squares[1][6] = new MapSquare(3);

			map.Flags = new[] { new Point(5, 4), new Point(10, 11), new Point(1, 6)};

			return map;
		}
	}
}
