#pragma once
#include "Card.h"
#include <vector>
class Hand
{
public:
	enum HandRanking {
		HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_KIND,
		STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
	};
	struct HandRating
	{
		int pokerHand;
		int handRank[5];
		int kickerRank[2];
	};
	Hand();
	virtual ~Hand();

	//virtual void getHandRank(HandRating& handRaiting);
	void add(Card* pCard);
	void add(vector<Card*>& aVector);
	void clear();
	vector<Card*> getHand() const;
	void additionalCard() const;

protected:
	vector<Card*> m_cards;
	//virtual void countRanks(int rankCount[]);
	//virtual void countSuits(int suitCount[]);
	//virtual void getFlushRank(HandRating& handRating, Card::suit);

	friend ostream& operator<<(ostream& os, Hand& aHand);
	friend bool operator>(HandRating& rating1, HandRating& rating2);
	friend bool operator< (HandRating& rating1, HandRating& rating2);
	friend bool operator==(HandRating& rating1, HandRating & rating2);

};

