#include "stdafx.h"
#include "Framework.h"

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

	void Framework::InitializeInstanceFields()
	{
		if (!initialized)
		{
			//	Enter the IP address of the server you are connecting to:
			ipAddress = "127.0.0.1";

			initialized = true;
		}
	}

	void Framework::Main(array<String^> ^args)
	{
		XmlConfigurator::Configure();
		if (log->IsInfoEnabled)
			log->Info("***** Windwardopolis starting *****");

		List<String^>^ argsIList = gcnew List<String^>;
		for each (String^ arg in args)
			argsIList->Add(arg);

		Framework ^framework = gcnew Framework(argsIList);
		framework->Run();
	}

	Framework::Framework(Collections::Generic::IList<String^> ^args)
	{
		InitializeInstanceFields();
		brain = gcnew MyPlayerBrain(args->Count >= 2 ? args[1] : nullptr);
		if (args->Count >= 1)
			ipAddress = args[0];
		String ^msg = String::Format("Connecting to server {0} for user: {1}", ipAddress, brain->Name);
		if (log->IsInfoEnabled)
			log->Info(msg);
		Console::Out->WriteLine(msg);
	}

	void Framework::Run()
	{
		Console::Out->WriteLine("starting...");

		tcpClient = gcnew TcpClient();
		tcpClient->Start(this, ipAddress);
		ConnectToServer();

		// It's all messages to us now.
		Console::Out->WriteLine("enter \"exit\" to exit program");
		while (true)
		{
			String ^line = Console::ReadLine();
			if (line->Equals("exit"))
				break;
		}
	}

	void Framework::StatusMessage(String ^message)
	{
		Console::Out->WriteLine(message);
	}

	List<Passenger^>^ getPassengers(array<String^> ^names, List<Passenger^> ^passengers)
	{
		List<Passenger^>^ subset = gcnew List<Passenger^>;
		for each(String^ name in names)
			for each(Passenger^ psngr in passengers)
				if (psngr->Name->Equals(name)) {
					subset->Add(psngr);
					break;
				}
		return subset;
	}

	void Framework::IncomingMessage(String ^message)
	{
		try
		{
			DateTime startTime = DateTime::Now;
			// get the xml - we assume we always get a valid message from the server.
			XmlDocument ^xml = gcnew XmlDocument; 
			xml->LoadXml(message);

			if (xml->DocumentElement->LocalName->Equals("setup"))
			{
					Console::Out->WriteLine("Received setup message");
					if (log->IsInfoEnabled)
						log->Info("Received setup message");

					List<Player^> ^players = Player::FromXml(safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("players")));
					List<Company^> ^companies = Company::FromXml(safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("companies")));
					List<Passenger^> ^passengers = Passenger::FromXml(safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("passengers")), companies);
					Map ^map = gcnew Map(safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("map")), companies);
					myGuid = xml->DocumentElement->GetAttribute("my-guid");
					Player ^me2 = findPlayer(players, myGuid);

					brain->Setup(map, me2, players, companies, passengers, gcnew PlayerAIBase::PlayerOrdersEvent(this, &Framework::PlayerOrdersEvent));

			}
			else if (xml->DocumentElement->LocalName->Equals("status"))
			{
					// may be here because re-started and got this message before the re-send of setup.
					if (String::IsNullOrEmpty(myGuid))
					{
						Trap::trap();
						return;
					}

					PlayerAIBase::STATUS status = safe_cast<PlayerAIBase::STATUS>(Enum::Parse(PlayerAIBase::STATUS::typeid, 
						xml->DocumentElement->GetAttribute("status")));
					XmlAttribute ^attr = xml->DocumentElement->GetAttributeNode("player-guid");
					String ^guid = attr != nullptr ? attr->Value : myGuid;

					System::Threading::Monitor::Enter(this);
					try
					{
						if (signal > 0)
						{
							// bad news - we're throwing this message away.
							Trap::trap();
							return;
						}
						signal++;
					}
					finally
					{
						System::Threading::Monitor::Exit(this);
					}

					Player::UpdateFromXml(brain->Players, brain->Passengers, safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("players")));
					Passenger::UpdateFromXml(brain->Passengers, brain->Companies, safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("passengers")));

					// update my path & pick-up.
					Player ^plyrStatus = findPlayer(brain->Players, guid);
					XmlElement ^elem = safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("path"));
					if (elem != nullptr)
					{
						array<String^> ^path = elem->InnerText->Split(gcnew array<Char> {';'}, StringSplitOptions::RemoveEmptyEntries);
						plyrStatus->Limo->Path->Clear();
						for each (String ^stepOn in path)
						{
							int pos = stepOn->IndexOf(',');
							plyrStatus->Limo->Path->Add(Point(Convert::ToInt32(stepOn->Substring(0, pos)), Convert::ToInt32(stepOn->Substring(0, pos))));
						}
					}

					elem = safe_cast<XmlElement^>(xml->DocumentElement->SelectSingleNode("pick-up"));
					if (elem != nullptr)
					{
						array<String^> ^names = elem->InnerText->Split(gcnew array<Char> {';'}, StringSplitOptions::RemoveEmptyEntries);
						plyrStatus->PickUp->Clear();
						for each (Passenger ^psngrOn in getPassengers(names, brain->Passengers))
							plyrStatus->PickUp->Add(psngrOn);
					}

					// pass in to generate new orders
					brain->GameStatus(status, plyrStatus, brain->Players, brain->Passengers);

					System::Threading::Monitor::Enter(this);
					try
					{
						signal--;
					}
					finally
					{
						System::Threading::Monitor::Exit(this);
					}

			}
			else if (xml->DocumentElement->LocalName->Equals("exit"))
			{
					Console::Out->WriteLine("Received exit message");
					if (log->IsInfoEnabled)
						log->Info("Received exit message");
					Environment::Exit(0);

			}
			else
			{
					Trap::trap();
					String ^msg = String::Format("ERROR: bad message (XML) from server - root node {0}", xml->DocumentElement->LocalName);
					log->Warn(msg);
					Trace::WriteLine(msg);
			}

			TimeSpan turnTime = DateTime::Now.Subtract(startTime);
			if (turnTime.TotalMilliseconds > 800)
				Console::Out->WriteLine("WARNING - turn took {0} seconds", turnTime.TotalMilliseconds / 1000);
		}
		catch (Exception ^ex)
		{
			Console::Out->WriteLine(String::Format("Error on incoming message. Exception: {0}", ex));
			log->Error("Error on incoming message.", ex);
		}
	}

	void Framework::PlayerOrdersEvent(String ^order, List<Point> ^path, List<Passenger^> ^pickUp)
	{

		// update our info
		if (path->Count > 0)
		{
			brain->Me->Limo->Path->Clear();
			brain->Me->Limo->Path->AddRange(path);
		}
		if (pickUp->Count > 0)
		{
			brain->Me->PickUp->Clear();
			brain->Me->PickUp->AddRange(pickUp);
		}

		XmlDocument ^xml = gcnew XmlDocument;
		XmlElement ^elem = xml->CreateElement(order);
		xml->AppendChild(elem);
		if (path->Count > 0)
		{
			StringBuilder ^buf = gcnew StringBuilder();
			for each (Point ptOn in path)
				buf->Append(Convert::ToString(ptOn.X) + L',' + Convert::ToString(ptOn.Y) + L';');
			XmlElement^ ndPath = xml->CreateElement("path");
			ndPath->InnerText = buf->ToString();
			elem->AppendChild(ndPath);
		}
		if (pickUp->Count > 0)
		{
			StringBuilder ^buf = gcnew StringBuilder();
			for each (Passenger ^psngrOn in pickUp)
				buf->Append(psngrOn->Name + L';');
			XmlElement^ ndPath = xml->CreateElement("pick-up");
			ndPath->InnerText = buf->ToString();
			elem->AppendChild(ndPath);
		}
		tcpClient->SendMessage(xml->OuterXml);
	}

	void Framework::ConnectionLost(Exception ^ex)
	{

		Console::Out->WriteLine("Lost our connection! Exception: " + ex->Message);
		log->Warn("Lost our connection!", ex);

		int delay = 500;
		while (true)
			try
			{
				if (tcpClient != nullptr)
					tcpClient->Close();
				tcpClient = gcnew TcpClient();
				tcpClient->Start(this, ipAddress);

				ConnectToServer();
				Console::Out->WriteLine("Re-connected");
				log->Warn("Re-connected");
				return;
			}
			catch (Exception ^e)
			{
				log->Warn("Re-connection fails!", e);
				Console::Out->WriteLine("Re-connection fails! Exception: " + e->Message);
				Thread::Sleep(delay);
				delay += 500;
			}
	}

	void Framework::ConnectToServer()
	{
		XmlDocument ^doc = gcnew XmlDocument;
		XmlElement ^root = doc->CreateElement("join");
		root->SetAttribute("name", brain->Name);
		root->SetAttribute("school", MyPlayerBrain::SCHOOL);
		root->SetAttribute("language", "C++");
		array<Byte> ^data = brain->Avatar;
		if (data != nullptr) {
			XmlElement^ ndAvatar = doc->CreateElement("avatar");
			ndAvatar->InnerText = Convert::ToBase64String(data);
			root->AppendChild(ndAvatar);
		}
		doc->AppendChild(root);
		tcpClient->SendMessage(doc->OuterXml);
	}

	
}
