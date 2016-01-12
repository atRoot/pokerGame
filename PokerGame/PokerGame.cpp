// PockerGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GeneralPlayer& aGeneralPlayer);
ostream& operator<<(ostream& os, const Hand& aHand);
int _tmain(int argc, _TCHAR* argv[])
{
	string myName;
	cout << "Welcome to pocker game" << endl;
	cout << "Enter your name: ";
	cin >> myName;
	cout << '\n' << "Hi " << myName << endl;
	Game aGame(myName);

	char again = 'y';
	while (again != 'n')
	{
		aGame.play();
		cout << "Do you want to play again? (y/n): ";
		cin >> again;
	}

	return 0;
}

ostream& operator<<(ostream& os, const Card& aCard)
{
	const string RANKS[] = {"2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K", "A" };
	const string SUITS[] = { "C", "D", "H", "S" };

	if (aCard.m_isFaceUp)
	{
		os << RANKS[aCard.m_rank]
			<< SUITS[aCard.m_suit];
	}
	else
		os << "XX";

	return os;
}

ostream& operator<<(ostream& os, const GeneralPlayer& aGeneralPlayer)
{
	os << aGeneralPlayer.m_name << ": ";

	vector<Card*>::const_iterator pCard;
	if (!aGeneralPlayer.m_cards.empty())
	{
		for (pCard = aGeneralPlayer.m_cards.begin();
			pCard != aGeneralPlayer.m_cards.end();
			++pCard)
		{
			os << *(*pCard) << " ";
		}
	}
	else
		os << "empty";
	return os;

}
ostream& operator<<(ostream& os, Hand& aHand)
{
	vector<Card*>::const_iterator pCard;
	if (!aHand.m_cards.empty())
	{
		for (pCard = aHand.m_cards.begin();
			pCard != aHand.m_cards.end();
			++pCard)
		{
			os << *(*pCard) << " ";
		}
	}
	else
		os << "empty";
	return os;
}