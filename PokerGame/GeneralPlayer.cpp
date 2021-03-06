#include "stdafx.h"
#include "GeneralPlayer.h"


GeneralPlayer::GeneralPlayer(const string& name) : m_name(name)
{
}

GeneralPlayer::~GeneralPlayer()
{
}

void GeneralPlayer::flipCards()
{
	if (!m_cards.empty())
	{
		for (int i = 0; i < m_cards.size(); ++i)
		{
			m_cards[i]->flip();
		}
	}
	else
		cout << "No cards to flip" << endl;
}

void GeneralPlayer::fold() const
{
	cout << m_name << "folded" << endl;
}
void GeneralPlayer::countRanks(int rankCount[], Hand& table)
{
	vector<Card*> tableCards;
	tableCards = table.getHand();

	for (int i = 0; i < m_cards.size(); ++i)
	{
		rankCount[m_cards[i]->getRank()]++;
	}
	for (int i = 0; i < tableCards.size(); ++i)
	{
		rankCount[tableCards[i]->getRank()];
	}
}
void GeneralPlayer::countSuits(int suitCount[], Hand& table)
{
	vector<Card*> tableCards;
	tableCards = table.getHand();

	for (int i = 0; i < m_cards.size(); ++i)
	{
		suitCount[m_cards[i]->getSuit()];
	}
	for (int i = 0; i < tableCards.size(); ++i)
	{
		suitCount[tableCards[i]->getSuit()];
	}
}
void GeneralPlayer::getFlushRank(Hand& table, GeneralPlayer::HandRating& handRating, const Card::suit suit)
{
	Hand showDownHand;
	showDownHand.add(m_cards);
	showDownHand.add(table.getHand());
	vector<Card*> showDownCards = showDownHand.getHand();
	for (int i = 12, j = 0; j < 5; ++j)
	{
		if (showDownCards[i]->getSuit() == suit)
			handRating.kickerRank[j] = i;
	}
}
void GeneralPlayer::getHandRank(Hand& table, GeneralPlayer::HandRating& rating)
{
	int rankCount[13] = { 0 };
	int suitCount[4] = { 0 };
	int straightCounter = 0;
	//int handRank = 0; // 0 means high card
	int pairsCount = 0;
	int pairs[2] = { -1, -1 };
	int three = -1;
	int four = -1;
	int straightPos = -1;
	countRanks(rankCount, table);
	countSuits(suitCount, table);

	for (int i = 12, j = 0; j != 5; --i, ++j)
	{
		if (rankCount[i] == 1)
			rating.kickerRank[j] = i;
	}

	for (int i = 0; i < 13; ++i)
	{
		if (rankCount[i] == 2)
			pairs[pairsCount++] = i;
		else if (rankCount[i] == 3)
			three = i;
		else if (rankCount[i] == 4)
			four = i;
		else if (rankCount[i] == 1)
		{
			++straightCounter;
			if (straightCounter >= 5)
				straightPos = i;
		}
		else
			straightCounter = 0;
	}
	if (pairsCount == 2)
	{
		rating.handRank1 = pairs[1]; // bigger first
		rating.handRank2 = pairs[0];
		rating.pokerHand = TWO_PAIR;
	}
	else if (pairsCount == 1)
	{
		rating.handRank1 = pairs[0];
		rating.pokerHand = ONE_PAIR;
	}

	if (three >= 0)
	{
		rating.handRank1 = three;
		rating.pokerHand = THREE_OF_KIND;
	}
	if (four >= 0)
	{
		rating.handRank1 = four;
		rating.pokerHand = FOUR_OF_KIND;
	}

	if (pairsCount == 1 && three >= 0)
	{
		rating.handRank1 = three;
		rating.handRank2 = pairs[0];
		rating.pokerHand = FULL_HOUSE;
	}
	if (straightPos >= 0)
	{
		rating.handRank1 = straightPos;
		rating.pokerHand = STRAIGHT;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (suitCount[i] == 5)
		{
			rating.pokerHand = FLUSH;
			getFlushRank(table, rating, static_cast<Card::suit>(i));
			if (straightPos >= 0)
			{
				rating.pokerHand = STRAIGHT_FLUSH;
				if (straightPos == 12)
					rating.pokerHand = ROYAL_FLUSH;
			}
		}
	}

}