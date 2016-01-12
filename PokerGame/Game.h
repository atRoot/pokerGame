#pragma once

#include "Deck.h"
#include "Player.h"
#include "CompPlayer.h"

class Game
{
public:
	friend ostream& operator<< (ostream& os, const Card& aCard);
	Game(const string& name);
	~Game();

	void play();

private:
	Deck m_deck;
	Player m_player;
	CompPlayer m_compPlayer;
	Hand m_table;
	void compareHands(Player& player, CompPlayer& compPlayer, Hand& table);



};

