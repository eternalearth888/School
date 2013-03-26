#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <cmath>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "FifoBuffer.h"
#include "IPlayerCallback.h"
#include "Trap.h"

using boost::asio::ip::tcp;
using std::string;
using std::vector;

namespace PlayerCSharpAI
{
	class TcpClient
	{

	public:
		TcpClient();
		~TcpClient();

		void Start(IPlayerCallback* callback, const string& address);

		void sendMessage(const string& msg);

		void Close();

	private:

		class ConnectionInfo
		{
		public:
			ConnectionInfo();
			~ConnectionInfo();

			tcp::socket* getSocket();
			void setSocket(tcp::socket* value);

			unsigned char* getSocketReadBuffer();
			void setSocketReadBuffer(unsigned char* value);

			// Appends bytesRead bytes from socketReadBuffer data to messageBuffer.
			void ReceivedData(int bytesRead);

			bool getHasMessage();
			string getMessage();
			

		private:
			tcp::socket* m_socket;

			// Buffer for receiving message chunks from socket.
			unsigned char* m_socketReadBuffer;

			// we store up a message here.
			// length:  0 => have less than 4 bytes in (including 0)
			//         >0 => have part/all of a message - length bytes have been removed from the buffer
			FifoByteBuffer*  m_messageBuffer;
			int m_messageLength;
			static const int MSG_LEN_BYTES = 4;
		};

		void ReceiveCallback(const boost::system::error_code& error, std::size_t bytes_transferred);

		static const int BUFFER_SIZE = 65536;
		
		boost::asio::io_service m_ioService;
		static const int PORT = 1707;
		tcp::endpoint* m_endpoint;
		boost::thread* m_socketThread;
		
		ConnectionInfo* m_connection;
		
		IPlayerCallback* m_playerCallback;

		boost::asio::io_service m_timerSvc;
		boost::asio::deadline_timer m_delayTimer;
	};
}

#endif