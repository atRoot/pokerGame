#include "stdafx.h"
#include "Game.h"


Game::Game(const vector<string>& names)
{
	//NUMBER_OF_PLAYERS = 4;
	m_players.reserve(names.size());

	const int COMP_PLAYERS = NUMBER_OF_PLAYERS - names.size();
	m_compPlayers.reserve(COMP_PLAYERS);

	for (int i =0; i< names.size(); ++i)
	{
		m_players.push_back(Player(names[i]));
	}
	for (int i = 0; i < COMP_PLAYERS; ++i)
	{
		string compPlayerName = "Comp player " + std::to_string(i);
		m_compPlayers.push_back(CompPlayer(compPlayerName));
	}
	srand(static_cast<unsigned int>(time(0)));
	m_deck.reset();
}

Game::~Game()
{
	//clear(m_players);
	//clear(m_compPlayers);
	m_players.clear();
	m_compPlayers.clear();
}

void Game::play()
{
	const int CARD_NUMBER = 2;
	//for (int i = 0; i <2 ; ++i)
	//{
	vector<Player>::iterator player = m_players.begin();
	for (; player != m_players.end(); ++player)
	{
		for (int i = 0; i< CARD_NUMBER; ++i)
			m_deck.deal(*(player));
		cout << *(player) << endl;
	}
	vector<CompPlayer>::iterator compPlayer = m_compPlayers.begin();
	for (; compPlayer != m_compPlayers.end(); ++compPlayer)
	{
		for (int i = 0; i< CARD_NUMBER; ++i)
			m_deck.deal(*(compPlayer));
		(compPlayer)->flipCards();
		cout << *(compPlayer) << endl;
	}

	m_deck.deal();
	for (int i = 0; i < 3; ++i)
	{
		m_deck.deal(m_table);
	}
	cout << "Table: " << endl;
	cout << m_table;
	
	//cout << "Press enter to continue" << endl;

	m_deck.deal();
	m_deck.deal(m_table);
	//cout << "Table: " << endl;
	//cout << m_table << endl;
	m_table.additionalCard();

	//cout << "Press enter to continue" << endl;

	m_deck.deal();
	m_deck.deal(m_table);
	m_table.additionalCard();

	compPlayer = m_compPlayers.begin();
	for (; compPlayer != m_compPlayers.end(); ++compPlayer)
	{
		(compPlayer)->flipCards();
		cout << '\n' << *(compPlayer) << endl;
	}

	//compareHands(m_player, m_compPlayer, m_table);
	announceWinner(m_players, m_compPlayers, m_table);

	clearPlayersHand(m_players);
	clearPlayersHand(m_compPlayers);
	m_table.clear();
	m_deck.reset();
}

void Game::announceWinner(vector<Player>& players, vector<CompPlayer>& compPlayers, Hand& table)
{
	vector<GeneralPlayer*> allPlayers;
	allPlayers.reserve(NUMBER_OF_PLAYERS);
	for (int i = 0; i < players.size(); ++i)
	{
		allPlayers.push_back(new Player(players[i]));
	}
	for (int i = 0; i < compPlayers.size(); ++i)
	{
		allPlayers.push_back(new CompPlayer(compPlayers[i]));
	}
	//const int ALL_PLAYER_SIZE = allPlayers.size();
	for (int i = 0; i < allPlayers.size(); ++i)
	{
		allPlayers[i]->add(table.getHand());
	}
	std::sort(allPlayers.begin(), allPlayers.end(), compareGreaterThan); // greaterThan is a friend of GeneralPlayer
	//clear(allPlayers);
}

void Game::clearPlayersHand(vector<GeneralPlayer*>& players)
{
	vector<GeneralPlayer*>::iterator player = players.begin();
	for (; player != players.end(); ++player)
	{
		(*player)->clear();
	}
}

void Game::clearPlayersHand(vector<Player>& players)
{
	vector<Player>::iterator player = players.begin();
	for (; player != players.end(); ++player)
	{
		(player)->clear();
	}
}

void Game::clearPlayersHand(vector<CompPlayer>& players)
{
	vector<CompPlayer>::iterator player = players.begin();
	for (; player != players.end(); ++player)
	{
		(player)->clear();
	}
}

void Game::clear(vector<GeneralPlayer*>& players)
{
	vector<GeneralPlayer*>::iterator iter = players.begin(); // important not to make any memory leaks
	for (; iter != players.end(); ++iter)
	{
		delete *iter;
		*iter = 0;
	}
	players.clear();
}
