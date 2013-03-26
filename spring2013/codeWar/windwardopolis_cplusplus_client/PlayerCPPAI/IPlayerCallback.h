#pragma once

	// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.


using namespace System;

namespace PlayerCPPAI
{
	public interface class IPlayerCallback
	{
		// Adds a message to the status window.
		// message: The message to add.
		void StatusMessage(String^);

		void IncomingMessage(String^);

		void ConnectionLost(Exception^);
	};
}
