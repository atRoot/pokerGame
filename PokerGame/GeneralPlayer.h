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
		int handRank1;
		int handRank2;
		int pokerHand;
		int kickerRank[5];
	};

	GeneralPlayer(const string& name = "");
	virtual ~GeneralPlayer();

	virtual int bidding() = 0; // const?
	void fold() const;
	void flipCards();

protected:
	string m_name;
	void countRanks(int rankCount[]);
	void countSuits(int suitCount[]);
	void getFlushRank(GeneralPlayer::HandRating& handRating, Card::suit);
	//int m_pokerHand;
	//int m_kickerRank;
	//HandRanking handRanking;
public:
	void getHandRank(HandRating& handRaiting);
	void win() const;
	void loose() const;
};

