#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "pugixml.hpp"
#include "IPlayerCallback.h"
#include "MyPlayerBrain.h"
#include "Point.h"
#include "TcpClient.h"

using pugi::xml_node;
using std::exception;
using std::string;
using std::vector;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{
	class Framework : public IPlayerCallback
	{
	public:
		Framework(int argc, char* argv[]);
		~Framework();

		void Run();

		void StatusMessage(const string& message);

		// handle an incoming message from the TcpClient
		void IncomingMessage(const string& message);
		
		void ConnectionLost(exception& ex);

	private:
		// Creates a list of points from the xml.
		// Caller is responsible for deleting the pointer.
		static vector<Point>* GetPoints(xml_node& element);

		void ConnectToServer();

		TcpClient* m_tcpClient;
		MyPlayerBrain* m_brain;
		string m_ipAddress;

		boost::asio::io_service m_timerSvc;
		boost::asio::deadline_timer m_delayTimer;
	};
}

#endif