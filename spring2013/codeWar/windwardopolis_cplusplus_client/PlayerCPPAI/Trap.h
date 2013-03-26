#pragma once

using namespace System;

// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

namespace PlayerCPPAI
{
	// Used to set code coverage breakpoints in the code in DEBUG mode only.
	public ref class Trap sealed abstract
	{
	private:
		// to turn breaks off in a debug session set this to false
		static bool stopOnBreak = true;

	public:
		// Will break in to the debugger (debug builds only).
		static void trap();

		// Will break in to the debugger if breakOn is true (debug builds only).
		// breakOn: Will break if this boolean value is true.
		static void trap(bool breakOn);
	};
}
