#pragma once

#include "IPlayerCallback.h"
#include "TcpClient.h"
#include "MyPlayerBrain.h"
#include "Player.h"
#include "Company.h"
#include "Passenger.h"
#include "Map.h"
#include "IPlayerAI.h"
#include "Trap.h"

// Created by Windward Studios, Inc. (www.windward.net). No copyright claimed - do anything you want with this code.

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Xml;
using namespace PlayerCPPAI::AI;
using namespace PlayerCPPAI::api;
using namespace log4net::Config;

namespace PlayerCPPAI
{
	public ref class Framework : IPlayerCallback
	{
	private:
		TcpClient ^tcpClient;
		initonly MyPlayerBrain ^brain;
		String ^ipAddress;

		String ^myGuid;

		// this is used to make sure we don't have multiple threads updating the Player/Passenger lists, sending
		// back multiple orders, etc. This is a lousy way to handle this - but it keeps the example simple and
		// leaves room for easy improvement.
		int signal;

		static initonly log4net::ILog ^log = log4net::LogManager::GetLogger(Framework::typeid);

		Framework(Collections::Generic::IList<String^> ^args);

		void Run();

		void PlayerOrdersEvent(String ^order, List<Point> ^path, List<Passenger^> ^pickUp);

		void ConnectToServer();

		bool initialized;
		void InitializeInstanceFields();

	public:
		// Run the A.I. player. All parameters are optional.
		//args: I.P. address of server, name
		static void Main(array<String^> ^args);

		virtual void StatusMessage(String ^message) sealed;

		virtual void IncomingMessage(String ^message) sealed;

		virtual void ConnectionLost(Exception ^ex) sealed;
	};
}

int main(array<String^> ^args)
{
	PlayerCPPAI::Framework::Main(args);

	return 0;
}
