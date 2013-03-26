#pragma once

#include "FifoBuffer.h"
#include "IPlayerCallback.h"

// code primarily from http://forum.codecall.net/classes-code-snippets/26089-c-example-high-performance-tcp-server-client.html
// Edited by Windward Studios, Inc. (www.windward.net). No copyright claimed by Windward on changes.

using namespace System;
using namespace System::Linq;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;

namespace PlayerCPPAI
{
	public ref class TcpClient
	{
	private:
		ref class ConnectionInfo
		{
		public:
			ConnectionInfo();

			property Socket ^Socket;
			property array<Byte> ^SocketReadBuffer;
			void ReceivedData(int bytesRead);

			property bool HasMessage
			{
				bool get();
			}

			property String ^Message
			{
				String ^get();
			}

		private:
			// we store up a message here.
			// length: 0  => have less than 4 bytes in (including 0)
			//         >0 => have part/all of a message - length bytes have been removed from the buffer
			initonly FifoByteBuffer ^messageBuffer;
			int messageLength;
		};

		literal int BUFFER_SIZE = 65536 * 4;
		literal int port = 1707;
		IPEndPoint ^clientEndpoint;
		ConnectionInfo ^connection;
		IPlayerCallback ^playerCallback;

		static initonly log4net::ILog ^log = log4net::LogManager::GetLogger(TcpClient::typeid);
		
		void ReceiveCallback(IAsyncResult ^result);

	public:
		void Start(IPlayerCallback ^callback, String ^address);

		void SendMessage(String ^msg);

		void Close();
	};
}
