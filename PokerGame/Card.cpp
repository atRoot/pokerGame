#include "stdafx.h"
#include "Card.h"


Card::Card(rank r, suit s, bool isFaceUp) : m_rank(r), m_suit(s), m_isFaceUp(isFaceUp)
{
}

int Card::getRank() const
{
	//card value is 0 while faced down
	int value = 0;
	if (m_isFaceUp)
	{
		value = m_rank;
	}
	return value;
}
int Card::getSuit() const // get rid of the o flip value in the future 
{
	int value = 0;
	if (m_isFaceUp)
	{
		value = m_suit;
	}
	return value;
}

void Card::flip()
{
	m_isFaceUp = !(m_isFaceUp);
}

Card::~Card()
{
}
