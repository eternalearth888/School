// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Drawing;
using System.Linq;
using System.Xml.Linq;

namespace PlayerCSharpAI.api
{
	/// <summary>
	/// The map of the game.
	/// </summary>
	public class GameMap
	{

		/// <summary>
		/// Create the map from the passed across XML
		/// </summary>
		/// <param name="element">The parent map node.</param>
		public GameMap(XElement element)
		{
			int width = int.Parse(element.Attribute("width").Value);
			int height = int.Parse(element.Attribute("height").Value);
			Squares = new MapSquare[width][];
			for (int x = 0; x < width; x++)
			{
				Squares[x] = new MapSquare[height];
				for (int y = 0; y < height; y++)
				{
					XElement elemSquare =
						(from sq in element.Elements("square")
						 where ((int) sq.Attribute("x") == x) && ((int) sq.Attribute("y") == y)
						 select sq).First();
					Squares[x][y] = new MapSquare(elemSquare);
				}
			}
		}

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
		public MapSquare [][] Squares { get; protected set; }

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

	}
}
