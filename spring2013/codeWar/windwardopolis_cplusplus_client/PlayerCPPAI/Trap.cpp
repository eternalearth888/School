#include "stdafx.h"
#include "Trap.h"

using namespace System;

namespace PlayerCPPAI
{

	void Trap::trap()
	{
	#if defined(DEBUG)
		if (stopOnBreak)
			System::Diagnostics::Debugger::Break();
	#endif
	}

	void Trap::trap(bool breakOn)
	{
	#if defined(DEBUG)
		if (stopOnBreak && breakOn)
			System::Diagnostics::Debugger::Break();
	#endif
	}
}
