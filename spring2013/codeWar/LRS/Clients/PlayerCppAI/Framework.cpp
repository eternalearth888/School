#include <fstream>
#include <iostream>
#include <sstream>
#include "encode.h"
#include "Framework.h"

using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_attribute;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::stringstream;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{

	Framework::Framework(int argc, char* argv[]) : m_timerSvc(), m_delayTimer(m_timerSvc)
	{
		char* name = NULL;
		if (argc > 2)
			name = argv[2];
		char* password = NULL;
		if (argc > 3)
			password = argv[3];
		m_brain = new MyPlayerBrain(name, password);
		if (argc > 1)
			m_ipAddress = argv[1];
		else
			m_ipAddress = "127.0.0.1";
	}

	Framework::~Framework()
	{
		delete m_tcpClient;
		delete m_brain;
	}

	void Framework::Run()
	{
		cout << "starting..." << endl;

		m_tcpClient = new TcpClient();
		m_tcpClient->Start(this, m_ipAddress);
		ConnectToServer();

		// It's all messages to us now.
		cout << "enter \"exit\" to exit program" << endl;
		char line[25];
		while (true)
		{
			cin.getline(line, 25, '\n');
			if (strcmp(line, "exit") == 0)
				break;
		}
	}

	void Framework::StatusMessage(const string& message)
	{
		Trap::trap();
		cout << message << endl;
	}

	void Framework::IncomingMessage(const string& message)
	{
		try
		{
			// get the xml - we assume we always get a valid message from the server.
			xml_document xml;
			xml.load(message.c_str());

			if (xml.child("start-position"))
			{
				xml_node ndPlayers = xml.first_child().child("players");
				vector<Player>* players = Player::FromXML(ndPlayers);
				string guid = xml.first_child().child("players").attribute("your-guid").value();
				Player* you;
				for (vector<Player>::iterator it = players->begin(); it != players->end(); ++it)
					if (*it->getGuid() == guid)
						you = &*it;
				GameMap* map = new GameMap(xml.first_child().child("map"));
				xml_node ndPt = xml.first_child().child("points");
				vector<Point>* startPts = GetPoints(ndPt);
				BoardLocation* start = m_brain->Setup(*map, *you, *players, *startPts, xml.root().attribute("game-start").as_bool());
				delete startPts;
				delete map;
				delete players;

				cout << "Starting robot at: " << start->toStr() << endl;
				xml_document doc;
				xml_node startPos = doc.append_child("start-position");
				start->makeAttributes(startPos);
				delete start;
				stringstream out;
				doc.print(out);
				m_tcpClient->sendMessage(out.str());
			}
			else if (xml.child("turn"))
			{
				int turnOn = xml.first_child().attribute("turn").as_int();
				cout << "turn " << turnOn << " request starting" << endl;
				// not used in this code, but you may wish to.
				bool repairSitesOn = xml.first_child().attribute("repair-on").as_bool();

				vector<Player>* allPlayers = Player::FromXML(xml.first_child().child("players"));
				string myGuid = xml.first_child().child("players").attribute("your-guid").value();
				Player* you;
				for (vector<Player>::iterator it = allPlayers->begin(); it != allPlayers->end(); ++it)
					if (*it->getGuid() == myGuid)
						you = &*it;
				xml_node ndCards = xml.first_child().child("cards");
				vector<Card>* newCards = Card::FromXML(ndCards);
				xml_node ndMap = xml.first_child().child("map");
				GameMap* map = new GameMap(ndMap);
				PlayerTurn* turn = m_brain->Turn(*map, *you, *allPlayers, *newCards);
				delete map;
				delete newCards;
				delete allPlayers;

				cout << "Turn: " << turnOn << " - " << turn->toStr() << endl;
				xml_document docTurn;
				xml_node ndRoot = docTurn.root();
				turn->makeXML(ndRoot);
				delete turn;
				docTurn.first_child().append_attribute("turn").set_value(turnOn);
				cout << "turn " << turnOn << " replying (after sleep)" << endl;
				stringstream out;
				docTurn.print(out);
				m_tcpClient->sendMessage(out.str());
			}
			else
			{
				Trap::trap();
				cout << "ERROR: bad message (XML) from server - root node " << xml.first_child().name() << endl;
			}
		}
		catch (exception& ex)
		{
			Trap::trap();
			cout << "Error on incoming message. Exception: " << ex.what() << endl;
		}
	}

	vector<Point>* Framework::GetPoints(xml_node & element)
	{
		xml_node pos = element.child("position");
		vector<Point>* v = new vector<Point>;
		for (xml_node pt = element.first_child(); pt; pt = pt.next_sibling())
			v->push_back(Point(pt.attribute("x").as_int(), pt.attribute("y").as_int()));
		return v;
	}

	void Framework::ConnectionLost(exception& ex)
	{

		cout << "Lost our connection! Exception: " << ex.what() << endl;

		int delay = 500;
		while (true)
			try
			{
				if (m_tcpClient != NULL) {
					try
					{
						m_tcpClient->Close();
					}
					catch (exception& e)
					{
						// nada
					}
					delete m_tcpClient;
					m_tcpClient = NULL;
				}
				m_tcpClient = new TcpClient();
				m_tcpClient->Start(this, "169.254.204.29");

				ConnectToServer();
				cout << "Re-connected" << endl;
				return;
			}
			catch (exception& e)
			{
				cout << "Re-connection fails! Exception: " << e.what() << endl;
				m_delayTimer.expires_from_now(boost::posix_time::milliseconds(delay));
				m_delayTimer.wait();
				delay += 500;
			}
	}

	void Framework::ConnectToServer()
	{
		xml_document doc;
		xml_node root = doc.append_child("join");
		root.append_attribute("password").set_value(m_brain->getPassword().c_str());
		root.append_attribute("name").set_value(m_brain->getName().c_str());

		try {
			std::ifstream avatarIn("MyAvatar.png", std::ios_base::in | std::ios_base::binary);
			if (!avatarIn.is_open())
				cerr << "Could not open avatar file!";
			else {
				base64::encoder E;
				stringstream  avatarOut;
				E.encode(avatarIn, avatarOut);

				avatarOut.seekg(0, ios::end);
				int avatarEncSize = avatarOut.tellg();
				avatarOut.seekg(0, ios::beg);

				char* avatarEnc = new char[avatarEncSize+1];
				avatarOut.read(avatarEnc, avatarEncSize);
				avatarEnc[avatarEncSize] = 0;

				std::ofstream tempOut("avatarEnc.txt", std::ios_base::out | std::ios_base::binary);
				tempOut.write(avatarEnc, avatarEncSize);
			
				xml_node ndAvatar = root.append_child("avatar");
				xml_node ndAvatarData = ndAvatar.append_child(pugi::node_pcdata);
				ndAvatarData.set_value(avatarEnc);

				delete [] avatarEnc;
			}
		}
		catch (...) {
			cerr << "Error loading avatar.";
		}

		stringstream out;
		doc.print(out);
		m_tcpClient->sendMessage(out.str());

		std::ofstream tempOut("connect.xml", std::ios_base::out | std::ios_base::binary);
		tempOut << out.str();
	}
}
