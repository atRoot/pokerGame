#pragma once
#include "Hand.h"
class Deck :
	public Hand
{
public:
	Deck();
	void populate();
	void shuffle();
	void deal(Hand& aHand); // to hand
	void deal(); // card away
	void additionalCards(Hand& aHand);
	void reset();
	virtual ~Deck();
};

