#include <climits>
#include <cstdlib>
#include <iostream>

#include "MyPlayerBrain.h"

using std::abs;
using std::rand;
using std::cout;
using std::endl;

using namespace PlayerCSharpAI::api;

namespace PlayerCSharpAI
{
	MyPlayerBrain::MyPlayerBrain(char* name, char* password)
	{
		if (name != NULL)
			m_name = name;
		else
			m_name="Donald Knuth";
		if (password != NULL)
			m_password = password;
		else
			m_password = "maryland";
	}

	string MyPlayerBrain::getName()
	{
		return m_name;
	}

	string MyPlayerBrain::getPassword()
	{
		return m_password;
	}

	Image* MyPlayerBrain::getAvatar()
	{
		return NULL;
	}

	PlayerCSharpAI::api::BoardLocation* MyPlayerBrain::Setup(GameMap& map, Player& you, vector<Player>& players, vector<Point>& robotStart, bool gameStart)
	{
		return new BoardLocation(robotStart.front(), MapSquareProperty::D_NORTH);
	}

	PlayerTurn* MyPlayerBrain::Turn(GameMap& map, Player& you, vector<Player>& allPlayers, vector<Card>& cards)
	{
		// if hurt bad, consider power down
		bool powerDown = false;
		if ((you.getDamage() > 5) && (rand() % 4 == 0))
			powerDown = true;

		// get 40 sets, pick the one that's closest to the flag
		vector<Card>* best = NULL;
		int bestDiff = INT_MAX;
		int okDiff = rand() % 3;
		FlagState* fs = NULL;
		vector<FlagState>* flags = you.getFlagStates();
		for (vector<FlagState>::iterator it = flags->begin(); it != flags->end(); ++it)
			if (!it->getTouched()) {
				fs = &*it;
				break;
			}
		Point ptFlag = fs == NULL ? Point(map.getWidth()/2, map.getHeight()/2) : fs->getPosition();
		for (int turnOn = 0; turnOn < 40; turnOn++)
		{
			// pick NUM_CARDS (or fewer if locked) random cards
			vector<Card>* moveCards = new vector<Card>();
			vector<bool> cardUsed(cards.size());
			for (int ind = 0; ind < NUM_CARDS - you.getNumLockedCards(); ind++)
				for (int iter = 0; iter < 100; iter++) // in case can't work it with these cards
				{
					int index = rand() % cards.size();
					if (cardUsed[index])
						continue;
					moveCards->push_back(cards[index]);
					cardUsed[index] = true;
					break;
				}

			// add in the locked cards
			for (int ind = NUM_CARDS - you.getNumLockedCards(); ind < NUM_CARDS; ind++)
				moveCards->push_back(you.getCards()->at(ind));

			// If all we have are rotates, we add in a move forward 1 so that a card that is a turn can then take into account next time we get a forward 1.
			bool addMove = true;
			for (vector<Card>::iterator it = moveCards->begin(); it != moveCards->end(); ++it)
				if (!it->isRotate()) {
					addMove = false;
					break;
				}
			if (addMove)
				moveCards->push_back(Card(Card::FORWARD_ONE, 500));

			// run it
			Utilities::MovePoint* mp = Utilities::CardDestination(map, *you.getRobot()->getLocation(), moveCards);
			
			// if it kills us we don't want it
			if (mp->getDead()) {
				delete mp;
				continue;
			}

			// if better than before, use it
			if (addMove)
				moveCards->pop_back();
			int diff = abs(ptFlag.X - mp->getLocation()->getMapPosition().X) + abs(ptFlag.Y - mp->getLocation()->getMapPosition().Y);
			if (diff <= okDiff) {
				delete mp;
				return new PlayerTurn(moveCards, powerDown);
			}
			if (diff < bestDiff)
			{
				bestDiff = diff;
				best = moveCards;
			}
			delete mp;
		}

		return new PlayerTurn(best == NULL ? new vector<Card>() : best, powerDown);
	}
}
