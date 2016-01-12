#pragma once
#include "Hand.h"
class GeneralPlayer :
	public Hand
{
	friend ostream& operator<<(ostream& os,
		const GeneralPlayer& aGeneralPlayer);

public:
	enum HandRanking {HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_KIND,
	STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH};
	struct HandRating
	{
		int pokerHand;
		int handRank1;
		int handRank2;
		int kickerRank[5];
	};

	GeneralPlayer(const string& name = "");
	virtual ~GeneralPlayer();

	virtual int bidding() = 0; // const?
	void fold() const;
	void flipCards();

protected:
	string m_name;
	void countRanks(int rankCount[], Hand& table);
	void countSuits(int suitCount[], Hand& table);
	void getFlushRank(Hand& table, GeneralPlayer::HandRating& handRating, Card::suit);
	//HandRanking handRanking;
public:
	void getHandRank(Hand& table, HandRating& handRaiting);
};

