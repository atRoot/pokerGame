#pragma once

#include "Deck.h"
#include "Player.h"
#include "CompPlayer.h"
#include <functional>
#include <algorithm>

class Game
{
	friend ostream& operator<< (ostream& os, const Card& aCard);

public:
	Game(const vector<string>& names);
	~Game();

	void play();

private:
	Deck m_deck;
	const int NUMBER_OF_PLAYERS = 4;
	//Player m_player;
	//CompPlayer m_compPlayer;
	vector<Player> m_players;
	vector<CompPlayer> m_compPlayers;
	Hand m_table;
	GeneralPlayer* compareHands(Player& player, CompPlayer& compPlayer, Hand& table);
	void clearPlayersHand(vector<Player>& players);
	void clearPlayersHand(vector<CompPlayer>& players);
	void announceWinner(vector<Player>& players, vector<CompPlayer>& compPlayers);
	void clearPlayersHand(vector<GeneralPlayer*>& players);
	void clear(vector<GeneralPlayer*>& players);

};

