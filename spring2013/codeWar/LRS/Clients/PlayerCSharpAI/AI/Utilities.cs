// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System;
using System.Collections.Generic;
using System.Drawing;
using PlayerCSharpAI.api;

namespace PlayerCSharpAI.AI
{
	/// <summary>
	/// Utilities that can be of use to an AI.
	/// </summary>
	public static class Utilities
	{

		/// <summary>
		/// Destination for a movement. Ignores all robots on the map but does take into account walls, conveyor belts and gears. Returns
		/// the final location of the move.
		/// </summary>
		/// <param name="map">The game map.</param>
		/// <param name="startLocation">Where the unit starts.</param>
		/// <param name="cards">The cards to apply.</param>
		/// <returns>The final location of the move.</returns>
		public static MovePoint CardDestination(GameMap map, BoardLocation startLocation, IEnumerable<Card> cards)
		{
			List<MovePoint> points = CardPath(map, startLocation, cards);
			if ((points == null) || (points.Count == 0))
				return null;
			return points[points.Count - 1];
		}

		/// <summary>
		/// Destination for a movement. Ignores all robots on the map but does take into account walls, conveyor belts and gears. Returns
		/// every step of the move.
		/// </summary>
		/// <param name="map">The game map.</param>
		/// <param name="startLocation">Where the unit starts.</param>
		/// <param name="cards">The cards to apply.</param>
		/// <returns>Every step of the move.</returns>
		public static List<MovePoint> CardPath(GameMap map, BoardLocation startLocation, IEnumerable<Card> cards)
		{
			// if we can't move, we end up where we started
			List<MovePoint> points = new List<MovePoint> {new MovePoint(startLocation)};

			foreach (Card cardOn in cards)
			{
				// move robot
				MovePoint endLocation = Move(map, startLocation, cardOn.Move);
				if (endLocation.Dead)
				{
					points.Add(endLocation);
					return points;
				}
				if (! endLocation.Location.Equals(startLocation))
				{
					startLocation = endLocation.Location;
					points.Add(new MovePoint(startLocation));
				}

				// conveyor belt - may cause a 1/4 turn.
				MapSquare sq = map.GetSquare(startLocation.MapPosition);
				for (int speed=1; (sq.Conveyor != null) && (speed <= sq.Conveyor.Speed); speed++)
				{
					endLocation = Move(map, startLocation.MapPosition, sq.Conveyor.Direction);
					BoardLocation locMove = new BoardLocation(endLocation.Location.MapPosition, startLocation.Direction);
					sq = map.GetSquare(endLocation.Location.MapPosition);
					if (sq.Conveyor != null)
					{
						MapSquare.DIRECTION dirEnter = MoveDirection(startLocation.MapPosition, endLocation.Location.MapPosition);
						locMove = locMove.Rotate((int)sq.Conveyor.Direction - (int)dirEnter);
					}
					startLocation = locMove;
					points.Add(new MovePoint(startLocation));
				}

				// gears
				if (sq.Type == MapSquare.TYPE.ROTATE_CLOCKWISE)
				{
					startLocation = startLocation.Rotate(1);
					points.Add(new MovePoint(startLocation));
				}
				if (sq.Type == MapSquare.TYPE.ROTATE_COUNTERCLOCKWISE)
				{
					startLocation = startLocation.Rotate(-1);
					points.Add(new MovePoint(startLocation));
				}

				// damage
				int damage = CalcLaserDamage(map, startLocation);
				if (damage != 0)
					points[points.Count - 1].Damage = damage;
			}

			return points;
		}

		/// <summary>
		/// Calculates what damage a unit will receive from lasers at a given location.
		/// </summary>
		/// <param name="map">The game map.</param>
		/// <param name="location">Where the unit is located.</param>
		/// <returns>The amount of damage. Will be 0 or 1.</returns>
		public static int CalcLaserDamage(GameMap map, BoardLocation location)
		{
			int damage = 0;
			damage += _CalcLaserDamage(map, location.MapPosition, 0, -1, MapSquare.DIRECTION.SOUTH, MapSquare.SIDE.NORTH, MapSquare.SIDE.SOUTH);
			damage += _CalcLaserDamage(map, location.MapPosition, 0, 1, MapSquare.DIRECTION.NORTH, MapSquare.SIDE.SOUTH, MapSquare.SIDE.NORTH);
			damage += _CalcLaserDamage(map, location.MapPosition, -1, 0, MapSquare.DIRECTION.EAST, MapSquare.SIDE.WEST, MapSquare.SIDE.EAST);
			damage += _CalcLaserDamage(map, location.MapPosition, 1, 0, MapSquare.DIRECTION.WEST, MapSquare.SIDE.EAST, MapSquare.SIDE.WEST);
			return damage;
		}

		private static int _CalcLaserDamage(GameMap map, Point position, int xAdd, int yAdd, MapSquare.DIRECTION laserDirection, MapSquare.SIDE wallExit, MapSquare.SIDE wallEnter)
		{
			int damage = 0;
			int x = position.X;
			int y = position.Y;
			bool startSquare = true;

			while ((0 <= x) && (x < map.Width) && (0 <= y) && (y < map.Height))
			{
				MapSquare sq = map.Squares[x][y];
				// can we move into this square?
				if ((! startSquare) && ((sq.Walls & wallEnter) != 0))
					break;
				startSquare = false;

				if ((sq.Laser != null) && (sq.Laser.Location.Direction == laserDirection))
				{
					damage++;
					break;
				}

				// can we move out of this square?
				if ((sq.Walls & wallExit) != 0)
					break;
				x += xAdd;
				y += yAdd;
			}
			return damage;
		}

		// NESW
		private static readonly MapSquare.SIDE[] sideMoveOut = { MapSquare.SIDE.NORTH, MapSquare.SIDE.EAST, MapSquare.SIDE.SOUTH, MapSquare.SIDE.WEST };
		private static readonly MapSquare.SIDE[] sideMoveIn = { MapSquare.SIDE.SOUTH, MapSquare.SIDE.WEST, MapSquare.SIDE.NORTH, MapSquare.SIDE.EAST };

		/// <summary>
		/// Move a unit one card move. Ignores all robots on the map but does take into account walls, conveyor belts and gears.
		/// </summary>
		/// <param name="map">The game map.</param>
		/// <param name="startLocation">Where the unit starts.</param>
		/// <param name="move">The move to apply.</param>
		/// <returns>The final location of the move.</returns>
		public static MovePoint Move(GameMap map, BoardLocation startLocation, Card.ROBOT_MOVE move)
		{
			int steps = 0;
			switch (move)
			{
				case Card.ROBOT_MOVE.BACKWARD_ONE:
					steps = -1;
					break;
				case Card.ROBOT_MOVE.FORWARD_ONE:
					steps = 1;
					break;
				case Card.ROBOT_MOVE.FORWARD_TWO:
					steps = 2;
					break;
				case Card.ROBOT_MOVE.FORWARD_THREE:
					steps = 3;
					break;
				case Card.ROBOT_MOVE.ROTATE_LEFT:
					return new MovePoint(startLocation.Rotate(-1));
				case Card.ROBOT_MOVE.ROTATE_RIGHT:
					return new MovePoint(startLocation.Rotate(1));
				case Card.ROBOT_MOVE.ROTATE_UTURN:
					return new MovePoint(startLocation.Rotate(2));
			}

			MapSquare.DIRECTION dir = steps >= 0 ? startLocation.Direction : startLocation.Rotate(2).Direction;
			Point position = startLocation.MapPosition;
			while (steps != 0)
			{
				MovePoint mp = Move(map, position, dir);
				if (mp.Dead)
					return new MovePoint(new BoardLocation(mp.Location.MapPosition, startLocation.Direction), true);
				position = mp.Location.MapPosition;
				int singleStep = Math.Max(-1, Math.Min(1, steps));
				steps -= singleStep;
			}
			return new MovePoint(new BoardLocation(position, startLocation.Direction));
		}

		/// <summary>
		/// Move a unit one square in the requested direction. Ignores all robots on the map but does take into account walls, conveyor belts and gears.
		/// </summary>
		/// <param name="map">The game map.</param>
		/// <param name="position">The map square to start the move from.</param>
		/// <param name="direction">The direction to move.</param>
		/// <returns>The final location of the move.</returns>
		public static MovePoint Move(GameMap map, Point position, MapSquare.DIRECTION direction)
		{

			// watch for wall in this direction
			MapSquare.SIDE sideExit = sideMoveOut[(int) direction];
			MapSquare.SIDE sideEnter = sideMoveIn[(int) direction];
			BoardLocation location = new BoardLocation(position, direction);

			// can we exit this square?
			MapSquare sq = map.GetSquare(position);
			if ((sq.Walls & sideExit) != 0)
				return new MovePoint(location);
			BoardLocation moveTo = location.Move(1);

			// did we go off the board?
			if ((moveTo.MapPosition.X < 0) || (map.Width <= moveTo.MapPosition.X) ||
				(moveTo.MapPosition.Y < 0) || (map.Height <= moveTo.MapPosition.Y))
				return new MovePoint(location, true);

			// did we go into a pit?
			if (map.GetSquare(moveTo.MapPosition).Type == MapSquare.TYPE.PIT)
				return new MovePoint(moveTo, true);

			// can we enter the new square?
			sq = map.GetSquare(moveTo.MapPosition);
			if ((sq.Walls & sideEnter) != 0)
				return new MovePoint(location);

			return new MovePoint(moveTo);
		}

		public static MapSquare.DIRECTION MoveDirection(Point start, Point end)
		{
			if (start.Y > end.Y)
				return MapSquare.DIRECTION.NORTH;
			if (start.Y < end.Y)
				return MapSquare.DIRECTION.SOUTH;
			if (start.X > end.X)
				return MapSquare.DIRECTION.WEST;
			if (start.X < end.X)
				return MapSquare.DIRECTION.EAST;
			throw new ApplicationException("start = end point " + start);
		}

		/// <summary>
		/// The result of one of the Utilities Move methods.
		/// </summary>
		public class MovePoint
		{
			/// <summary>
			/// Create the object. No damage and not dead.
			/// </summary>
			/// <param name="location">The location of the move result.</param>
			public MovePoint(BoardLocation location)
			{
				Location = location;
				Damage = 0;
				Dead = false;
			}

			/// <summary>
			/// Create the object. Not dead.
			/// </summary>
			/// <param name="location">The location of the move result.</param>
			/// <param name="damage">The damage level from this move.</param>
			public MovePoint(BoardLocation location, int damage)
			{
				Location = location;
				Damage = damage;
			}

			/// <summary>
			/// Create the object. No damage.
			/// </summary>
			/// <param name="location">The location of the move result.</param>
			/// <param name="dead">true if the move caused death.</param>
			public MovePoint(BoardLocation location, bool dead)
			{
				Location = location;
				Dead = dead;
			}

			/// <summary>
			/// The location of the move result.
			/// </summary>
			public BoardLocation Location { get; private set; }

			/// <summary>
			/// The damage level received from this move.
			/// </summary>
			public int Damage { get; set; }

			/// <summary>
			/// true if the move caused the unit to die (moved off the board).
			/// </summary>
			public bool Dead { get; private set; }
		}
	}
}
