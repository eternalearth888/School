

using System.Drawing;

namespace RoboRallyNet.game_engine
{
	public interface ISprite
	{
		// return true to kill it
		bool IncreaseTick();

		Image SpriteBitmap { get; }
	}
}
