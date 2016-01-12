#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>

using namespace std;

#pragma once
class Card
{
public:

	enum rank {TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
	enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
	
	// overloading << operator so send Card object to std output
	friend ostream& operator<< (ostream& os, const Card& aCard);

	Card(rank r = ACE, suit s = SPADES, bool isFaceUp = true);
	~Card();
	int getRank() const;
	int getSuit() const;
	void flip();

private:
	rank m_rank;
	suit m_suit;
	bool m_isFaceUp;

	
};

