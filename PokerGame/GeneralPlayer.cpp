#include "stdafx.h"
#include "GeneralPlayer.h"


GeneralPlayer::GeneralPlayer(Hand& table, const string& name) : m_name(name), m_table(table)
{
}

GeneralPlayer::~GeneralPlayer()
{
}

void GeneralPlayer::win() const
{
	cout << m_name << " wins" << endl;
}
void GeneralPlayer::loose() const
{
	cout << m_name << " loose" << endl;
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

Hand& GeneralPlayer::getTable() const
{
	return m_table;
}

void GeneralPlayer::fold() const
{
	cout << m_name << "folded" << endl;
}

void GeneralPlayer::countRanks(int rankCount[])
{
	vector<Card*> tableCards;
	tableCards = m_table.getHand();
	for (int i = 0; i < m_cards.size(); ++i)
	{
		rankCount[m_cards[i]->getRank()]++;
	}
	for (int i = 0; i < tableCards.size(); ++i)
	{
		rankCount[tableCards[i]->getRank()]++;
	}
}
void GeneralPlayer::countSuits(int suitCount[])
{
	vector<Card*> tableCards;
	tableCards = m_table.getHand();
	for (int i = 0; i < m_cards.size(); ++i)
	{
		suitCount[m_cards[i]->getSuit()]++;
	}
	for (int i = 0; i < tableCards.size(); ++i)
	{
		suitCount[tableCards[i]->getSuit()]++;
	}
}
void GeneralPlayer::getFlushRank(Hand::HandRating& handRating, const Card::suit suit)
{
	vector<Card*> tableCards;
	tableCards = m_table.getHand();

	for (int i = 12, j = 0, t = 0;i < 0; --i)
	{
		if (t < 2)
		{
			if (m_cards[t++]->getSuit() == suit)
				handRating.handRank[j++] = i;
		}
		if (tableCards[j]->getSuit() == suit)
			handRating.handRank[j++] = i;
		if (j == 5)
			break;
	}
}

void GeneralPlayer::getHandRank(Hand::HandRating& rating)
{
	const int SUIT_COUNT = 4;
	int rankCount[13] = { 0 };
	int suitCount[4] = { 0 };
	int straightCounter = 0;
	//int handRank = 0; // 0 means high card
	int pairsCount = 0;
	int pairs[2] = { -1, -1 };
	int three = -1;
	int four = -1;
	int straightPos = -1;
	countRanks(rankCount);
	countSuits(suitCount);

	//for (int i = 12, j = 0; j != 5; --i, ++j)
	//{
	//	if (rankCount[i] == 1)
	//		rating.kickerRank[j] = i;
	//}
	if (m_cards[0]->getRank() > m_cards[1]->getRank())
	{
		rating.kickerRank[0] = m_cards[0]->getRank();
		rating.kickerRank[1] = m_cards[1]->getRank();
	}
	else
	{
		rating.kickerRank[1] = m_cards[0]->getRank();
		rating.kickerRank[0] = m_cards[1]->getRank();
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
		rating.handRank[0] = pairs[1]; // bigger first
		rating.handRank[1] = pairs[0];
		rating.pokerHand = TWO_PAIR;
	}
	else if (pairsCount == 1)
	{
		rating.handRank[0] = pairs[0];
		rating.pokerHand = ONE_PAIR;
	}

	if (three >= 0)
	{
		rating.handRank[0] = three;
		rating.pokerHand = THREE_OF_KIND;
	}
	if (four >= 0)
	{
		rating.handRank[0] = four;
		rating.pokerHand = FOUR_OF_KIND;
	}

	if (pairsCount == 1 && three >= 0)
	{
		rating.handRank[0] = three;
		rating.handRank[1] = pairs[0];
		rating.pokerHand = FULL_HOUSE;
	}
	if (straightPos >= 0)
	{
		rating.handRank[0] = straightPos;
		rating.pokerHand = STRAIGHT;
	}

	for (int i = 0; i < SUIT_COUNT; ++i)
	{
		if (suitCount[i] >= 5)
		{
			rating.pokerHand = FLUSH;
			getFlushRank(rating, static_cast<Card::suit>(i));
			if (straightPos >= 0)
			{
				rating.pokerHand = STRAIGHT_FLUSH;
				if (straightPos == 12)
					rating.pokerHand = ROYAL_FLUSH;
			}
		}
	}

}

bool operator> (GeneralPlayer& player1, GeneralPlayer& player2)
{
	Hand::HandRating player1Rating = { -1, {-1, -1, -1, -1, -1}, {-1, -1} }; // init struct members
	Hand::HandRating player2Rating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } };
	//Hand::HandRating tableRating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } };
	//Hand& table = player1.getTable();
	//table.getHandRank(tableRating); // a work around to get a object member to static function
	player1.getHandRank(player1Rating);
	player2.getHandRank(player2Rating);

	if (player1Rating > player2Rating)
		return true;
	else
		return false;
}

bool operator< (GeneralPlayer& player1, GeneralPlayer& player2)
{
	Hand::HandRating player1Rating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } }; // init struct members
	Hand::HandRating player2Rating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } }; // init struct members
	//Hand::HandRating tableRating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } };
	player1.getHandRank(player1Rating);
	player2.getHandRank(player2Rating);

	if (player1Rating < player2Rating)
		return true;
	else
		return false;
}


bool operator==(GeneralPlayer& player1, GeneralPlayer& player2)
{
	Hand::HandRating player1Rating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } }; // init struct members
	Hand::HandRating player2Rating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } };
	//Hand::HandRating tableRating = { -1, { -1, -1, -1, -1, -1 }, { -1, -1 } };
	//Hand& table = player1.getTable();
	//table.getHandRank(tableRating); // a work around to get a object member to static function
	player1.getHandRank(player1Rating);
	player2.getHandRank(player2Rating);

	if (player1Rating == player2Rating)
		return true;
	else
	{
		return false;
	}
}
//bool compareGreaterThan(GeneralPlayer *player1, GeneralPlayer *player2)
//{
//	
//	GeneralPlayer::HandRating player1Rating;
//	GeneralPlayer::HandRating player2Rating;
//	player1->getHandRank(player1Rating);
//	player2->getHandRank(player2Rating);
//
//	if (player1Rating.pokerHand == player2Rating.pokerHand) //combinations from strongest to weakest
//	{
//		switch (player1Rating.pokerHand)
//		{
//		case GeneralPlayer::ROYAL_FLUSH:
//			return false;
//			break;
//		case GeneralPlayer::STRAIGHT_FLUSH:
//			if (player1Rating.handRank1 > player2Rating.handRank1) // checks whose show down is in higher ranking
//				return true;
//			else
//				return false;
//			break;
//		case GeneralPlayer::FOUR_OF_KIND:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//				return true;
//			else if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.kickerRank > player2Rating.kickerRank)
//					return true;
//				else
//					return false;
//			}
//			return false;
//			break;
//		case GeneralPlayer::FULL_HOUSE:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//			{
//				return true;
//			}
//			else if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.handRank2 > player2Rating.handRank2)
//					return true;
//				else
//					return false;
//			}
//			return false;
//			break;
//		case GeneralPlayer::FLUSH:
//			for (int i = 0; i < 5; ++i)
//			{
//				if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
//				{
//					return true;
//				}
//			}
//			return false;
//			break;
//		case GeneralPlayer::STRAIGHT:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//			{
//				return true;
//			}
//			else
//				return false;
//			break;
//		case GeneralPlayer::THREE_OF_KIND:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//			{
//				return true;
//			}
//			else if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				for (int i = 0; i < 2; ++i)
//				{
//					if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
//					{
//						return true;
//					}
//
//				}
//				return false;
//			}
//			return false;
//			break;
//		case GeneralPlayer::TWO_PAIR:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//			{
//				return true;
//			}
//			else if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.handRank2 > player2Rating.handRank2)
//				{
//					return true;
//				}
//				else if (player1Rating.handRank2 == player2Rating.handRank2)
//				{
//					if (player1Rating.kickerRank[0] > player2Rating.kickerRank[0])
//					{
//						return true;
//					}
//					else
//						return false;
//				}
//
//			}
//			return false;
//			break;
//		case GeneralPlayer::ONE_PAIR:
//			if (player1Rating.handRank1 > player2Rating.handRank1)
//			{
//				return true;
//			}
//			else if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				for (int i = 0; i < 3; ++i)
//				{
//					if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
//					{
//						return true;
//					}
//				}
//			}
//			return false;
//			break;
//		case GeneralPlayer::HIGH_CARD:
//
//			for (int i = 0; i < 5; ++i)
//			{
//				if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
//				{
//					return true;
//				}
//			}
//			return false;
//			break;
//		default:
//			return false;
//			break;
//		}
//	}
//	else if (player1Rating.pokerHand > player2Rating.pokerHand)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//bool compareEquals(GeneralPlayer *player1, GeneralPlayer *player2)
//{
//
//	GeneralPlayer::HandRating player1Rating;
//	GeneralPlayer::HandRating player2Rating;
//	player1->getHandRank(player1Rating);
//	player2->getHandRank(player2Rating);
//
//	if (player1Rating.pokerHand == player2Rating.pokerHand) //combinations from strongest to weakest
//	{
//		switch (player1Rating.pokerHand)
//		{
//		case GeneralPlayer::ROYAL_FLUSH:
//			return true;
//			break;
//		case GeneralPlayer::STRAIGHT_FLUSH:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//				return true;
//			else
//				return false;
//			break;
//		case GeneralPlayer::FOUR_OF_KIND:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.kickerRank == player2Rating.kickerRank)
//					return true;
//			}
//			return false;
//			break;
//		case GeneralPlayer::FULL_HOUSE:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.handRank2 == player2Rating.handRank2)
//					return true;
//			}
//			return false;
//			break;
//		case GeneralPlayer::FLUSH:
//			for (int i = 0; i < 5; ++i)
//			{
//				if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
//				{
//					return false;
//				}
//			}
//			return true;
//			break;
//		case GeneralPlayer::STRAIGHT:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				return true;
//			}
//			return false;
//			break;
//		case GeneralPlayer::THREE_OF_KIND:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				for (int i = 0; i < 2; ++i)
//				{
//					if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
//					{
//						return false;
//					}
//				}
//				return true;
//			}
//			return false;
//			break;
//		case GeneralPlayer::TWO_PAIR:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				if (player1Rating.handRank2 == player2Rating.handRank2)
//				{
//					if (player2Rating.kickerRank[0] == player2Rating.kickerRank[0])
//					{
//						return true;
//					}
//				}
//
//			}
//			return false;
//			break;
//		case GeneralPlayer::ONE_PAIR:
//			if (player1Rating.handRank1 == player2Rating.handRank1)
//			{
//				for (int i = 0; i < 3; ++i)
//				{
//					if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
//					{
//						return false;
//					}
//				}
//				return true;
//			}
//			return false;
//			break;
//		case GeneralPlayer::HIGH_CARD:
//
//			for (int i = 0; i < 5; ++i)
//			{
//				if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
//				{
//					return false;
//				}
//			}
//			return true;
//			break;
//		default:
//			return false;
//			break;
//		}
//	}
//	else {
//		return false;
//	}
//}
//bool operator> (GeneralPlayer& player1, GeneralPlayer& player2)
//{
//	return false;
//}
//
//
//bool operator== (GeneralPlayer& player1, GeneralPlayer& player2)
//{
//	return false;
//}