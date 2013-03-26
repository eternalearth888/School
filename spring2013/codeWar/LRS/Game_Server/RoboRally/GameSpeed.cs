
using System.Windows.Forms;

namespace RoboRallyNet
{
	public partial class GameSpeed : Form
	{
		public GameSpeed(int movesPerSecond)
		{
			InitializeComponent();
			spinMovesPerSec.Value = movesPerSecond;
		}

		public int MovesPerSecond
		{
			get { return (int) spinMovesPerSec.Value; }
		}
	}
}
