// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using System.Drawing;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// A sprite on the map.
	/// </summary>
	internal class Sprite
	{
		/// <summary>
		/// Called once each tick (used for animation).
		/// </summary>
		/// <returns>true to kill this sprite, false to keep it alive.</returns>
		public virtual bool IncreaseTick()
		{
			return false;
		}

		/// <summary>
		/// The map square this sprite is centered in.
		/// </summary>
		public virtual Point Location
		{
			get { return Point.Empty; }
		}

		/// <summary>
		/// The bitmap for this sprite. This will change on ticks for animated sprites.
		/// </summary>
		public virtual Image SpriteBitmap
		{
			get { return new Bitmap(0, 0); }
		}
	}
}
