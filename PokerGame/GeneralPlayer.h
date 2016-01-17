#pragma once
#include "Hand.h"
class GeneralPlayer :
	public Hand
{
	friend ostream& operator<<(ostream& os,
		const GeneralPlayer& aGeneralPlayer);
	friend bool operator< (GeneralPlayer& player1, GeneralPlayer& player2);
	friend bool operator> (GeneralPlayer& player1, GeneralPlayer& player2);
	friend bool operator== (GeneralPlayer& player1, GeneralPlayer& player2);
	friend bool compareGreaterThan(GeneralPlayer *player1, GeneralPlayer *player2);
	friend bool compareEquals(GeneralPlayer* player1, GeneralPlayer* player2);

public:
	GeneralPlayer(Hand& table, const string& name = "");
	virtual ~GeneralPlayer();

	virtual int bidding() = 0; // const?
	void fold() const;
	void flipCards();
	Hand& getTable() const;
	void getHandRank(HandRating& handRaiting);


protected:
	string m_name;
	Hand &m_table;
	void countRanks(int rankCount[]);
	void countSuits(int suitCount[]);
	void getFlushRank(HandRating& handRating, Card::suit);
	
	//bool compGreaterThan(GeneralPlayer *player1, GeneralPlayer *player2);
	//bool compEquals(GeneralPlayer *player1, GeneralPlayer *player2);
	//int m_pokerHand;
	//int m_kickerRank;
	//HandRanking handRanking;
public:
	void win() const;
	void loose() const;
};

