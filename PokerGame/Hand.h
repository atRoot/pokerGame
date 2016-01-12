#pragma once
#include "Card.h"
#include <vector>
class Hand
{
	friend ostream& operator<<(ostream& os, Hand& aHand);
public:
	Hand();
	virtual ~Hand();

	void add(Card* pCard);
	void add(vector<Card*>& aVector);
	void clear();
	vector<Card*> getHand() const;
	void additionalCard() const;

protected:
	vector<Card*> m_cards;



};

