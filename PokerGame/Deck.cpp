#include "stdafx.h"
#include "Deck.h"


Deck::Deck()
{
	m_cards.reserve(52);
	populate();
}

Deck::~Deck()
{
}

void Deck::populate()
{
	clear();
	for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
	{
		for (int r = Card::TWO; r <= Card::ACE; ++r)
		{
			add(new Card(static_cast<Card::rank>(r),
				static_cast<Card::suit>(s)));
		}
	}
}
void Deck::shuffle()
{
	random_shuffle(m_cards.begin(), m_cards.end());
}
void Deck::reset()
{
	populate();
	shuffle();
}
void Deck::deal(Hand& aHand)
{
	if (!m_cards.empty())
	{
		aHand.add(m_cards.back());
		m_cards.pop_back();
	}
	else
		cout << "Out of cards" << endl;
}
void Deck::deal()
{
	if (!m_cards.empty())
	{
		m_cards.pop_back();
	}
	else
		cout << "Out of cards" << endl;
}