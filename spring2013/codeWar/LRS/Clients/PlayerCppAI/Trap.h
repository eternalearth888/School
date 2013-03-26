#ifndef TRAP_H
#define TRAP_H

namespace PlayerCSharpAI
{
	/// Used to set code coverage breakpoints in the code in DEBUG mode only.
	class Trap
	{
	public:
		// Will break in to the debugger (debug builds only).
		static void trap();

		/// Will break in to the debugger if breakOn is true (debug builds only).
		/// <param name="breakOn">Will break if this boolean value is true.</param>
		static void trap(bool breakOn);

	private:
		// to turn breaks off in a debug session set this to false
		static bool stopOnBreak;
	};
}

#endif