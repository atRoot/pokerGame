#pragma once

#include "Deck.h"
#include "Player.h"
#include "CompPlayer.h"

class Game
{
public:
	friend ostream& operator<< (ostream& os, const Card& aCard);
	Game(const vector<string>& names); // dd
	~Game();

	void play();

private:
	Deck m_deck;
	Player m_player;
	CompPlayer m_compPlayer;
	vector<GeneralPlayer*> m_players;
	Hand m_table;
	void compareHands(Player& player, CompPlayer& compPlayer, Hand& table);



};

