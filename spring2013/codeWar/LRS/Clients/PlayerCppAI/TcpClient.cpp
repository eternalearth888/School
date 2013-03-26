#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include "EncodingMock.h"
#include "PlayerCppAIException.h"
#include "TcpClient.h"

using std::copy;
using std::exception;
using std::strlen;
using std::cout;
using std::endl;

typedef boost::asio::ip::address ip_address;

namespace PlayerCSharpAI
{
	// ConnectionInfo Begin

	TcpClient::ConnectionInfo::ConnectionInfo() : m_messageBuffer(new FifoByteBuffer(BUFFER_SIZE * 2))
	{
		m_socket = NULL;
		m_socketReadBuffer = new unsigned char[BUFFER_SIZE];
		m_messageLength = 0;
	}

	TcpClient::ConnectionInfo::~ConnectionInfo()
	{
		delete m_socket;
		delete [] m_socketReadBuffer;
		delete m_messageBuffer;
	}

	tcp::socket* TcpClient::ConnectionInfo::getSocket()
	{
		return m_socket;
	}

	void TcpClient::ConnectionInfo::setSocket(tcp::socket* value)
	{
		delete m_socket;
		m_socket = value;
	}

	unsigned char* TcpClient::ConnectionInfo::getSocketReadBuffer()
	{
		return m_socketReadBuffer;
	}

	void TcpClient::ConnectionInfo::setSocketReadBuffer(unsigned char* value)
	{
		delete m_socketReadBuffer;
		m_socketReadBuffer = value;
	}

	void TcpClient::ConnectionInfo::ReceivedData(int bytesRead)
	{
		m_messageBuffer->Write(m_socketReadBuffer, 0, bytesRead);
	}

	bool TcpClient::ConnectionInfo::getHasMessage()
	{
		// we may need to extract the length
		if (m_messageLength == 0 && m_messageBuffer->getCount() >= MSG_LEN_BYTES) {
			unsigned char* bytes = m_messageBuffer->Read(MSG_LEN_BYTES);
			m_messageLength = BitConverter::ToInt32(bytes);
			delete [] bytes;
		}
		return m_messageLength > 0 && m_messageLength <= m_messageBuffer->getCount();
	}

	string TcpClient::ConnectionInfo::getMessage()
	{
		//TODO: currently cheating with GetString. consider using pugi xml_node.
		string rtn = UTF8Enc::GetString(m_messageBuffer->Read(m_messageLength));
		m_messageLength = 0;
		return rtn;
	}

	// ConnectionInfo End

	TcpClient::TcpClient() : m_ioService(), m_timerSvc(), m_delayTimer(m_timerSvc)
	{
		m_endpoint = NULL;
		m_socketThread = NULL;
		m_connection = new ConnectionInfo;
		m_playerCallback = NULL;
	}

	TcpClient::~TcpClient()
	{
		delete m_endpoint;
		delete m_socketThread;
		delete m_connection;
		m_connection = NULL;
	}

	void TcpClient::Start(IPlayerCallback* callback, const string& address)
	{
		m_playerCallback = callback;
		ip_address addr = ip_address::from_string(address);
		m_endpoint = new tcp::endpoint(addr, PORT);

		tcp::socket* socket = new tcp::socket(m_ioService);
		//TODO: boost throws an exception when I make these calls. perhaps the size is too large.
		//socket->set_option(boost::asio::socket_base::send_buffer_size(BUFFER_SIZE));
		//socket->set_option(boost::asio::socket_base::receive_buffer_size(BUFFER_SIZE));
		m_connection->setSocket(socket);
		socket->connect(*m_endpoint);

		socket->async_receive(boost::asio::buffer(m_connection->getSocketReadBuffer(), BUFFER_SIZE), 
			boost::bind(&TcpClient::ReceiveCallback, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		m_socketThread = new boost::thread(boost::bind(&boost::asio::io_service::run, &m_ioService));
	}

	void TcpClient::ReceiveCallback(const boost::system::error_code& error, size_t bytes_transferred)
	{
		try
		{
			if (error) {
				Close();
				return;
			}

			if (error == boost::asio::error::eof)
			{
				cout << "\n\nEOF received.\n\n";
			}

			//TODO:
			//lock (connection)
				m_connection->ReceivedData(bytes_transferred);

			// only way we have multiple messages is an error on the server side - but that could happen.
			while (true)
			{
				string message;
				//TODO:
				//lock (connection)
				//{
					if (!m_connection->getHasMessage())
						break;
					message = m_connection->getMessage();
				//}
				m_playerCallback->IncomingMessage(message);
			}

			m_connection->getSocket()->async_receive(boost::asio::buffer(m_connection->getSocketReadBuffer(), BUFFER_SIZE), 
				boost::bind(&TcpClient::ReceiveCallback, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		catch (exception& ex)
		{
			Close();
			m_playerCallback->ConnectionLost(ex);
		}
	}

	void TcpClient::sendMessage(const string& msg)
	{
		const char* bytes = msg.c_str();
		size_t bytesLen = strlen(bytes);
		unsigned char* length = BitConverter::GetBytes(bytesLen);
		// assuming 4-byte little endian integers
		boost::system::error_code ignoredError;
		boost::asio::write(*m_connection->getSocket(), boost::asio::buffer(length, 4), ignoredError);
		delete [] length;
		Trap::trap(bytesLen > BUFFER_SIZE);
		boost::asio::write(*m_connection->getSocket(), boost::asio::buffer(bytes, bytesLen), ignoredError);
	}

	void TcpClient::Close()
	{
		if (m_connection == NULL)
			return;
		try
		{
			if (m_connection->getSocket()->is_open())
				m_connection->getSocket()->close();
		}
		catch (exception& e1)
		{
			// nada
			Trap::trap();
		}

		delete m_connection;
		m_connection = NULL;
		
		m_delayTimer.expires_from_now(boost::posix_time::milliseconds(50));
		m_delayTimer.wait();
	}
}
