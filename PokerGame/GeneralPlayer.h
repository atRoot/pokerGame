#pragma once
#include "Hand.h"
class GeneralPlayer :
	public Hand
{
	friend ostream& operator<<(ostream& os,
		const GeneralPlayer& aGeneralPlayer);
	//friend bool operator> (GeneralPlayer& player1, GeneralPlayer& player2);
	//friend bool operator== (GeneralPlayer& player1, GeneralPlayer& player2);
	friend bool compareGreaterThan(GeneralPlayer *player1, GeneralPlayer *player2);


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
	GeneralPlayer(const GeneralPlayer& player);
	virtual ~GeneralPlayer();

	virtual int bidding() = 0; // const?
	void fold() const;
	void flipCards();

protected:
	string m_name;
	void countRanks(int rankCount[]);
	void countSuits(int suitCount[]);
	void getFlushRank(GeneralPlayer::HandRating& handRating, Card::suit);
	bool compGreaterThan(GeneralPlayer *player1, GeneralPlayer *player2);
	bool compEquals(GeneralPlayer *player1, GeneralPlayer *player2);
	//int m_pokerHand;
	//int m_kickerRank;
	//HandRanking handRanking;
public:
	void getHandRank(HandRating& handRaiting);
	void win() const;
	void loose() const;
};

