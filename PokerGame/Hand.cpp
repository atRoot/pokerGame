#include "stdafx.h"
#include "Hand.h"


Hand::Hand()
{
	m_cards.reserve(7);
}

Hand::~Hand()
{
	clear();
}
void Hand::add(Card* pCard)
{
	m_cards.push_back(pCard);
}
void Hand::add(vector<Card*>& aVector)
{
	m_cards.insert(m_cards.end(), aVector.begin(), aVector.end());
}
void Hand::additionalCard() const
{
	cout << *(m_cards.back())<< " ";
}
void Hand::clear()
{
	vector<Card*>::iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		delete *iter;
		*iter = 0;
	}
	m_cards.clear();
}

vector<Card*> Hand::getHand() const
{
	return m_cards;
}

//void Hand::countRanks(int rankCount[])
//{
//	for (int i = 0; i < m_cards.size(); ++i)
//	{
//		rankCount[m_cards[i]->getRank()]++;
//	}
//}
//void Hand::countSuits(int suitCount[])
//{
//	for (int i = 0; i < m_cards.size(); ++i)
//	{
//		suitCount[m_cards[i]->getSuit()];
//	}
//}
//void Hand::getFlushRank(Hand::HandRating& handRating, const Card::suit suit)
//{
//	for (int i = 12, j = 0; j < 5; ++j)
//	{
//		if (m_cards[i]->getSuit() == suit)
//			handRating.handRank[j] = i;
//	}
//}

//void Hand::getHandRank(Hand::HandRating& rating)
//{
//	const int SUIT_COUNT = 4;
//	int rankCount[13] = { 0 };
//	int suitCount[4] = { 0 };
//	int straightCounter = 0;
//	//int handRank = 0; // 0 means high card
//	int pairsCount = 0;
//	int pairs[2] = { -1, -1 };
//	int three = -1;
//	int four = -1;
//	int straightPos = -1;
//	countRanks(rankCount);
//	countSuits(suitCount);
//
//	//for (int i = 12, j = 0; j != 5; --i, ++j)
//	//{
//	//	if (rankCount[i] == 1)
//	//		rating.kickerRank[j] = i;
//	//}
//	/*if (m_cards[0]->getRank() > m_cards[1]->getRank())
//	{
//		rating.kickerRank[0] = m_cards[0]->getRank();
//		rating.kickerRank[1] = m_cards[1]->getRank();
//	}
//	else
//	{
//		rating.kickerRank[1] = m_cards[0]->getRank();
//		rating.kickerRank[0] = m_cards[1]->getRank();
//	}*/
//
//
//	for (int i = 0; i < 13; ++i)
//	{
//		if (rankCount[i] == 2)
//			pairs[pairsCount++] = i;
//		else if (rankCount[i] == 3)
//			three = i;
//		else if (rankCount[i] == 4)
//			four = i;
//		else if (rankCount[i] == 1)
//		{
//			++straightCounter;
//			if (straightCounter >= 5)
//				straightPos = i;
//		}
//		else
//			straightCounter = 0;
//	}
//	if (pairsCount == 2)
//	{
//		rating.handRank[0] = pairs[1]; // bigger first
//		rating.handRank[1] = pairs[0];
//		rating.pokerHand = TWO_PAIR;
//	}
//	else if (pairsCount == 1)
//	{
//		rating.handRank[0] = pairs[0];
//		rating.pokerHand = ONE_PAIR;
//	}
//
//	if (three >= 0)
//	{
//		rating.handRank[0] = three;
//		rating.pokerHand = THREE_OF_KIND;
//	}
//	if (four >= 0)
//	{
//		rating.handRank[0] = four;
//		rating.pokerHand = FOUR_OF_KIND;
//	}
//
//	if (pairsCount == 1 && three >= 0)
//	{
//		rating.handRank[0] = three;
//		rating.handRank[1] = pairs[0];
//		rating.pokerHand = FULL_HOUSE;
//	}
//	if (straightPos >= 0)
//	{
//		rating.handRank[0] = straightPos;
//		rating.pokerHand = STRAIGHT;
//	}
//
//	for (int i = 0; i < SUIT_COUNT; ++i)
//	{
//		if (suitCount[i] == 5)
//		{
//			rating.pokerHand = FLUSH;
//			getFlushRank(rating, static_cast<Card::suit>(i));
//			if (straightPos >= 0)
//			{
//				rating.pokerHand = STRAIGHT_FLUSH;
//				if (straightPos == 12)
//					rating.pokerHand = ROYAL_FLUSH;
//			}
//		}
//	}
//
//}

bool operator> (Hand::HandRating& rating1, Hand::HandRating& rating2)
{
	const int HAND_RANK_COUNT = 5;
	const int KICKER_COUNT = 2;
	if (rating1.pokerHand > rating2.pokerHand)
		return true;
	else if (rating1.pokerHand < rating2.pokerHand)
		return false;

	for (int i = 0; i < HAND_RANK_COUNT; ++i)
	{
		if (rating1.handRank[i] > rating2.handRank[i])
			return true;
		else if (rating1.handRank[i] < rating2.handRank[i])
			return false;
	}
	for (int i = 0; i < KICKER_COUNT; ++i)
	{
		if (rating1.kickerRank[i] > rating2.kickerRank[i])
			return true;
	}
	return false;
}

bool operator< (Hand::HandRating& rating1, Hand::HandRating& rating2)
{
	const int HAND_RANK_COUNT = 5;
	const int KICKER_COUNT = 2;
	if (rating1.pokerHand < rating2.pokerHand)
		return true;
	else if (rating1.pokerHand > rating2.pokerHand)
		return false;

	for (int i = 0; i < HAND_RANK_COUNT; ++i)
	{
		if (rating1.handRank[i] < rating2.handRank[i])
			return true;
		else if (rating1.handRank[i] > rating2.handRank[i])
			return false;
	}
	for (int i = 0; i < KICKER_COUNT; ++i)
	{
		if (rating1.kickerRank[i] < rating2.kickerRank[i])
			return true;
	}
	return false;
}

bool operator== (Hand::HandRating& rating1, Hand::HandRating& rating2)
{
	const int HAND_RANK_COUNT = 5;
	const int KICKER_COUNT = 2;
	if (rating1.pokerHand == rating2.pokerHand)
	{
		for (int i = 0; i < HAND_RANK_COUNT; ++i)
		{
			if (rating1.handRank[i] != rating2.handRank[i])
			{
				return false;
			}
		}
		for (int i = 0; i < KICKER_COUNT; ++i)
		{
			if (rating1.kickerRank[i] != rating2.kickerRank[i])
				return false;
		}
		return true;
	}
	else
		return false;
}