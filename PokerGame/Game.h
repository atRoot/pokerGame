#pragma once

#include "Deck.h"
#include "Player.h"
#include "CompPlayer.h"
#include <functional>

class Game
{
public:
	friend ostream& operator<< (ostream& os, const Card& aCard);
	
	Game(const vector<string>& names);
	~Game();

	void play();

private:
	Deck m_deck;
	const int NUMBER_OF_PLAYERS = 4;
	//Player m_player;
	//CompPlayer m_compPlayer;
	vector<GeneralPlayer*> m_players;
	vector<GeneralPlayer*> m_compPlayers;
	Hand m_table;
	GeneralPlayer* compareHands(Player& player, CompPlayer& compPlayer, Hand& table);
	//void clearPlayersHand(vector<Player>& players);
	//void clearPlayersHand(vector<CompPlayer>& players);
	void announceWinner(vector<GeneralPlayer*> players, vector<GeneralPlayer*> compPlayers, Hand table);
	void clearPlayersHand(vector<GeneralPlayer*>& players);
	void clear(vector<GeneralPlayer*>& players);

};

