#include "stdafx.h"
#include "GeneralPlayer.h"


GeneralPlayer::GeneralPlayer(const string& name) : m_name(name)
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

void GeneralPlayer::fold() const
{
	cout << m_name << "folded" << endl;
}
void GeneralPlayer::countRanks(int rankCount[])
{
	for (int i = 0; i < m_cards.size(); ++i)
	{
		rankCount[m_cards[i]->getRank()]++;
	}
}
void GeneralPlayer::countSuits(int suitCount[])
{
	for (int i = 0; i < m_cards.size(); ++i)
	{
		suitCount[m_cards[i]->getSuit()];
	}
}
void GeneralPlayer::getFlushRank(GeneralPlayer::HandRating& handRating, const Card::suit suit)
{
	for (int i = 12, j = 0; j < 5; ++j)
	{
		if (m_cards[i]->getSuit() == suit)
			handRating.kickerRank[j] = i;
	}
}

void GeneralPlayer::getHandRank(GeneralPlayer::HandRating& rating)
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
	countRanks(rankCount);
	countSuits(suitCount);

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
	GeneralPlayer::HandRating player1Rating;
	GeneralPlayer::HandRating player2Rating;
	player1.getHandRank(player1Rating);
	player2.getHandRank(player2Rating);

	if (player1Rating.pokerHand == player2Rating.pokerHand) //combinations from strongest to weakest
	{
		switch (player1Rating.pokerHand)
		{
		case GeneralPlayer::ROYAL_FLUSH:
			return false;
			break;
		case GeneralPlayer::STRAIGHT_FLUSH:
			if (player1Rating.handRank1 > player2Rating.handRank1) // checks whose show down is in higher ranking
				return true;
			else
				return false;
			break;
		case GeneralPlayer::FOUR_OF_KIND:
			if (player1Rating.handRank1 > player2Rating.handRank1)
				return true;
			else if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.kickerRank > player2Rating.kickerRank)
					return true;
				else
					return false;
			}
			return false;
			break;
		case GeneralPlayer::FULL_HOUSE:
			if (player1Rating.handRank1 > player2Rating.handRank1)
			{
				return true;
			}
			else if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.handRank2 > player2Rating.handRank2)
					return true;
				else
					return false;
			}
			return false;
			break;
		case GeneralPlayer::FLUSH:
			for (int i = 0; i < 5; ++i)
			{
				if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
				{
					return true;
				}
			}
			return false;
			break;
		case GeneralPlayer::STRAIGHT:
			if (player1Rating.handRank1 > player2Rating.handRank1)
			{
				return true;
			}
			else
				return false;
			break;
		case GeneralPlayer::THREE_OF_KIND:
			if (player1Rating.handRank1 > player2Rating.handRank1)
			{
				return true;
			}
			else if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
					{
						return true;
					}

				}
				return false;
			}
			return false;
			break;
		case GeneralPlayer::TWO_PAIR:
			if (player1Rating.handRank1 > player2Rating.handRank1)
			{
				return true;
			}
			else if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.handRank2 > player2Rating.handRank2)
				{
					return true;
				}
				else if (player1Rating.handRank2 == player2Rating.handRank2)
				{
					if (player2Rating.kickerRank[0] > player2Rating.kickerRank[0])
					{
						return true;
					}
					else
						return false;
				}

			}
			return false;
			break;
		case GeneralPlayer::ONE_PAIR:
			if (player1Rating.handRank1 > player2Rating.handRank1)
			{
				return true;
			}
			else if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				for (int i = 0; i < 3; ++i)
				{
					if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
					{
						return true;
					}

				}
			}
			return false;
			break;
		case GeneralPlayer::HIGH_CARD:

			for (int i = 0; i < 5; ++i)
			{
				if (player1Rating.kickerRank[i] > player2Rating.kickerRank[i])
				{
					return true;
				}
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	else if (player1Rating.pokerHand > player2Rating.pokerHand)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool operator== (GeneralPlayer& player1, GeneralPlayer& player2)
{
	GeneralPlayer::HandRating player1Rating;
	GeneralPlayer::HandRating player2Rating;
	player1.getHandRank(player1Rating);
	player2.getHandRank(player2Rating);
	bool playerWon = true;
	bool isSplit = false;

	if (player1Rating.pokerHand == player2Rating.pokerHand) //combinations from strongest to weakest
	{
		switch (player1Rating.pokerHand)
		{
		case GeneralPlayer::ROYAL_FLUSH:
			return true;
			break;
		case GeneralPlayer::STRAIGHT_FLUSH:
			if (player1Rating.handRank1 == player2Rating.handRank1)
				return true;
			else
				return false;
			break;
		case GeneralPlayer::FOUR_OF_KIND:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.kickerRank == player2Rating.kickerRank)
					return true;
			}
			return false;
			break;
		case GeneralPlayer::FULL_HOUSE:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.handRank2 == player2Rating.handRank2)
					return true;
			}
			return false;
			break;
		case GeneralPlayer::FLUSH:
			for (int i = 0; i < 5; ++i)
			{
				if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
				{
					return false;
				}
			}
			return true;
			break;
		case GeneralPlayer::STRAIGHT:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				return true;
			}
			return false;
			break;
		case GeneralPlayer::THREE_OF_KIND:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
			break;
		case GeneralPlayer::TWO_PAIR:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				if (player1Rating.handRank2 == player2Rating.handRank2)
				{
					if (player2Rating.kickerRank[0] == player2Rating.kickerRank[0])
					{
						return true;
					}
				}

			}
			return false;
			break;
		case GeneralPlayer::ONE_PAIR:
			if (player1Rating.handRank1 == player2Rating.handRank1)
			{
				for (int i = 0; i < 3; ++i)
				{
					if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
					{
						return false;
					}
				}
				return true;
			}
			break;
		case GeneralPlayer::HIGH_CARD:

			for (int i = 0; i < 5; ++i)
			{
				if (player1Rating.kickerRank[i] != player2Rating.kickerRank[i])
				{
					return false;
				}
			}
			return true;
			break;
		default:
			return false;
			break;
		}
	}
}