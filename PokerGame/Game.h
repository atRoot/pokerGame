#pragma once

#include "Deck.h"
#include "Player.h"
#include "CompPlayer.h"

class Game
{
public:
	friend ostream& operator<< (ostream& os, const Card& aCard);
	friend bool operator> (GeneralPlayer& player1, GeneralPlayer& player2);
	friend bool operator== (GeneralPlayer& player1, GeneralPlayer& player2);

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
	void announceWinner(vector<Player> players, vector<CompPlayer> compPlayers, Hand table);




};

