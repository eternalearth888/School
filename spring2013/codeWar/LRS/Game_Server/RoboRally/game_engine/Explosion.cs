using System.Drawing;

namespace RoboRallyNet.game_engine
{
	/// <summary>
	/// An explosion on the screen.
	/// </summary>
	class Explosion : Sprite
	{
		private readonly int startTick;
		private int tickOn;
		private readonly Point mapPosition;

		/// <summary>
		/// Create the explosion object.
		/// </summary>
		/// <param name="frameTicks">The number of ticks into the game at this point.</param>
		/// <param name="mapPosition">The map square to display this explosion on.</param>
		public Explosion(int frameTicks, Point mapPosition)
		{
			startTick = tickOn = frameTicks;
			this.mapPosition = mapPosition;
		}

		/// <summary>
		/// Called once each tick (used for animation).
		/// </summary>
		/// <returns>true to kill this sprite, false to keep it alive.</returns>
		public override bool IncreaseTick()
		{
			tickOn++;
			return tickOn > startTick + 12;
		}

		/// <summary>
		/// The map square this sprite is centered in.
		/// </summary>
		public override Point Location
		{
			get { return mapPosition; }
		}

		/// <summary>
		/// The bitmap for this sprite. This will change on ticks for animated sprites.
		/// </summary>
		public override Image SpriteBitmap
		{
			get {
				if (tickOn < startTick + 4)
					return Sprites.Explosion1;
				if (tickOn < startTick + 8)
					return Sprites.Explosion2;
				return Sprites.Explosion3;
			}
		}
	}
}
