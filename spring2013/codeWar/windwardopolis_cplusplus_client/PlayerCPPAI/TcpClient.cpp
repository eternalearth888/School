#include "stdafx.h"
#include "TcpClient.h"

using namespace System;
using namespace System::Linq;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::Threading;
namespace PlayerCPPAI
{

	TcpClient::ConnectionInfo::ConnectionInfo()
	{
		messageBuffer = gcnew FifoByteBuffer(BUFFER_SIZE * 2);
		SocketReadBuffer = gcnew array<Byte>(BUFFER_SIZE);
	}

	void TcpClient::ConnectionInfo::ReceivedData(int bytesRead)
	{
		messageBuffer->Write(SocketReadBuffer, 0, bytesRead);
	}

	bool TcpClient::ConnectionInfo::HasMessage::get()
	{
		// we may need to extract the length
		if (messageLength == 0 && messageBuffer->Count >= 4)
			messageLength = BitConverter::ToInt32(messageBuffer->Read(4), 0);
		return messageLength > 0 && messageLength <= messageBuffer->Count;
	}

	String ^TcpClient::ConnectionInfo::Message::get()
	{
		String ^rtn = Encoding::UTF8->GetString(messageBuffer->Read(messageLength));
		messageLength = 0;
		return rtn;
	}

	bool IsNotIP(String ^s) 
	{
		for each(wchar_t c in s) {
			if (!Char::IsNumber(c) && c == L'.')
				return true;
		}
		return false;
	}

	void TcpClient::Start(IPlayerCallback ^callback, String ^address)
	{

		// lookup IP address if name
		if (IsNotIP(address))
		{
			array<IPAddress^> ^addresslist = Dns::GetHostAddresses(address);
			address = addresslist[0]->ToString();
		}

		playerCallback = callback;
		IPAddress ^add = IPAddress::Parse(address);
		clientEndpoint = gcnew IPEndPoint(add, port);

		Socket ^clientSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		clientSocket->SendBufferSize = BUFFER_SIZE;
		clientSocket->ReceiveBufferSize = BUFFER_SIZE;
		connection = gcnew ConnectionInfo;
		connection->Socket = clientSocket;
		connection->Socket->Connect(clientEndpoint);
		;
		connection->Socket->BeginReceive(connection->SocketReadBuffer, 0, connection->SocketReadBuffer->Length, SocketFlags::None, 
			gcnew AsyncCallback(this, &TcpClient::ReceiveCallback), connection);
	}

	void TcpClient::ReceiveCallback(IAsyncResult ^result)
	{
		ConnectionInfo ^info = safe_cast<ConnectionInfo^>(result->AsyncState);
		try
		{
			int bytesRead = info->Socket->EndReceive(result);
			if (0 == bytesRead)
			{
				Close();
				return;
			}

			System::Threading::Monitor::Enter(connection);
			try
			{
				connection->ReceivedData(bytesRead);
			}
			finally
			{
				System::Threading::Monitor::Exit(connection);
			}

			// only way we have multiple messages is an error on the server side - but that could happen.
			while (true)
			{
				String ^message;
				System::Threading::Monitor::Enter(connection);
				try
				{
					if (!connection->HasMessage)
						break;
					message = connection->Message;
				}
				finally
				{
					System::Threading::Monitor::Exit(connection);
				}
				playerCallback->IncomingMessage(message);
			}

			connection->Socket->BeginReceive(connection->SocketReadBuffer, 0, connection->SocketReadBuffer->Length, SocketFlags::None, 
				gcnew AsyncCallback(this, &TcpClient::ReceiveCallback), connection);
		}
		catch (Exception ^ex)
		{
			Close();
			playerCallback->ConnectionLost(ex);
		}
	}

	void TcpClient::SendMessage(String ^msg)
	{
		if (String::IsNullOrEmpty(msg))
		{
			log->Warn("ERROR sending 0 byte message");
			Console::Out->WriteLine("ERROR sending 0 byte message");
			return;
		}
		try
		{
			array<Byte> ^bytes = Encoding::UTF8->GetBytes(msg);
			array<Byte> ^length = BitConverter::GetBytes(bytes->Length);
			connection->Socket->Send(length, length->Length, SocketFlags::None);
			for (int offset = 0; offset < bytes->Length; offset += BUFFER_SIZE)
				connection->Socket->Send(bytes, offset, Math::Min(bytes->Length - offset, BUFFER_SIZE), SocketFlags::None);
		}
		catch (Exception ^ex)
		{
			log->Warn("ERROR sending message", ex);
			Console::Out->WriteLine(String::Format("ERROR sending message - exception: {0}", ex));
		}
	}

	void TcpClient::Close()
	{
		if (connection == nullptr)
			return;
		try
		{
			if (connection->Socket->Connected)
				connection->Socket->Close();
		}
		catch (Exception ^e1)
		{
			// nada
		}
		connection = nullptr;
		Thread::Sleep(50);
	}
}
