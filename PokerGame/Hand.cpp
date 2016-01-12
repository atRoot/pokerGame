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
