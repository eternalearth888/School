#ifndef I_PLAYER_CALLBACK_H
#define I_PLAYER_CALLBACK_H

#include <exception>
#include <string>

namespace PlayerCSharpAI
{
	class IPlayerCallback
	{
	public:
		/// Adds a message to the status window.
		/// message: The message to add.
		virtual void StatusMessage(const std::string&) = 0;

		virtual void IncomingMessage(const std::string&) = 0;

		virtual void ConnectionLost(std::exception&) = 0;
	};
}

#endif