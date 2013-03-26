using System.Collections.Generic;
using System.Drawing;
using System.Xml.Linq;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A location and direction on the board.
	/// </summary>
	public struct BoardLocation
	{
		private Point _mapPosition;
		private MapSquare.DIRECTION _direction;

		/// <summary>
		/// A null location (off the board).
		/// </summary>
		public static BoardLocation NULL = new BoardLocation(new Point(-1, -1), MapSquare.DIRECTION.NORTH);

		/// <summary>
		/// Create the object
		/// </summary>
		/// <param name="mapPosition">The board square loacted on.</param>
		/// <param name="direction">The direction pointed to on the board.</param>
		public BoardLocation(Point mapPosition, MapSquare.DIRECTION direction)
		{
			_mapPosition = mapPosition;
			_direction = direction;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="src">Initialize with the values in this struct.</param>
		public BoardLocation(BoardLocation src)
		{
			_mapPosition = src.MapPosition;
			_direction = src.Direction;
		}

		public List<XAttribute> Attributes
		{
			get
			{
				return new List<XAttribute>
				       	{
				       		new XAttribute("direction", Direction),
				       		new XAttribute("x", MapPosition.X),
				       		new XAttribute("y", MapPosition.Y)
				       	};
			}
		}

		/// <summary>
		/// True if this location is null (placed at -1, -1).
		/// </summary>
		public bool IsNull
		{
			get { return _mapPosition.X == -1 || _mapPosition.Y == -1; }
		}

		/// <summary>
		/// The location on the map for this unit. Generally (-1, -1) if the unit is dead.
		/// </summary>
		public Point MapPosition
		{
			get { return _mapPosition; }
			set { _mapPosition = value; }
		}

		/// <summary>
		/// The direction this unit is facing. Ignored if the unit is dead.
		/// </summary>
		public MapSquare.DIRECTION Direction
		{
			get { return _direction; }
			set { _direction = value; }
		}

		/// <summary>
		/// Return a new struct moved the requested number of squares in the location's direction. This can move off the 
		/// board and is not blocked by units or walls.
		/// </summary>
		/// <param name="num">The number of map squares to move.</param>
		/// <returns>A new struct at the location moved to.</returns>
		public BoardLocation Move(int num)
		{
			switch (Direction)
			{
				case MapSquare.DIRECTION.NORTH:
					return new BoardLocation(new Point(MapPosition.X, MapPosition.Y - num), Direction);
				case MapSquare.DIRECTION.SOUTH:
					return new BoardLocation(new Point(MapPosition.X, MapPosition.Y + num), Direction);
				case MapSquare.DIRECTION.EAST:
					return new BoardLocation(new Point(MapPosition.X + num, MapPosition.Y), Direction);
				case MapSquare.DIRECTION.WEST:
					return new BoardLocation(new Point(MapPosition.X - num, MapPosition.Y), Direction);
			}
			return new BoardLocation(MapPosition, Direction);
		}

		/// <summary>
		/// Rotate the direction in a clockwise direction (NESW) the number of turns requested. A value of 4 results in a full circle.
		/// </summary>
		/// <param name="num">The number of quarter turns to make. Can be negative or positive. Can be outside the range of -3 .. 3.</param>
		/// <returns>A new struct at the location turned to.</returns>
		public BoardLocation Rotate(int num)
		{
			int dir = (int) (Direction + num);
			while (dir < 0)
				dir += 4;
			while (dir >= 4)
				dir -= 4;
			return new BoardLocation(MapPosition, (MapSquare.DIRECTION) dir);
		}

		/// <summary>
		/// Equality operator.
		/// </summary>
		/// <param name="obj">The BoardLocation to compare to.</param>
		/// <returns>true if both objects are at the same position in the same direction.</returns>
		public override bool Equals(object obj)
		{
			BoardLocation loc = (BoardLocation) obj;
			return Direction == loc.Direction && MapPosition == loc.MapPosition;
		}

		/// <summary>
		/// The hash code.
		/// </summary>
		/// <returns>The hash code.</returns>
		public override int GetHashCode()
		{
			return Direction.GetHashCode() ^ MapPosition.GetHashCode();
		}

		/// <summary>
		/// Displays the value of the object.
		/// </summary>
		/// <returns>The value of the object.</returns>
		public override string ToString()
		{
			return string.Format("{0} - {1}", MapPosition, Direction);
		}
	}
}
