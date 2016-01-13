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
		string compPlayerName = "Comp player " + std::to_string(++i);
		m_compPlayers.push_back(CompPlayer(compPlayerName));
	}
	srand(static_cast<unsigned int>(time(0)));
	m_deck.reset();
}

Game::~Game()
{
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
			m_deck.deal(*player);
		cout << *player << endl;
	}
	vector<CompPlayer>::iterator compPlayer = m_compPlayers.begin();
	for (; compPlayer != m_compPlayers.end(); ++compPlayer)
	{
		for (int i = 0; i< CARD_NUMBER; ++i)
			m_deck.deal(*compPlayer);
		compPlayer->flipCards();
		cout << *compPlayer << endl;
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
		compPlayer->flipCards();
		cout << '\n' << *compPlayer << endl;
	}

	compareHands(m_player, m_compPlayer, m_table);

	clearPlayersHand(m_players);
	clearPlayersHand(m_compPlayers);
	m_table.clear();
	m_deck.reset();
}

void Game::announceWinner(vector<Player>& players, vector<CompPlayer>& compPlayers, Hand& table)
{
	vector<GeneralPlayer&> allPlayers;
	allPlayers.reserve(NUMBER_OF_PLAYERS);
	int j = 0;
	for (int i = 0; i < players.size(); ++i)
	{
		allPlayers.push_back(players[i]);
	}
	for (int i = 0; i < compPlayers.size(); ++i)
	{
		allPlayers.push_back(compPlayers[i]);
	}

}

void Game::clearPlayersHand(vector<Player>& players)
{
	vector<Player>::iterator player = players.begin();
	for (; player != players.end(); ++player)
	{
		player->clear();
	}
}

void Game::clearPlayersHand(vector<CompPlayer>& players)
{
	vector<CompPlayer>::iterator player = players.begin();
	for (; player != players.end(); ++player)
	{
		player->clear();
	}
}

void Game::compareHands(Player& player, CompPlayer& compPlayer, Hand& table)
{
	GeneralPlayer::HandRating playerRating;
	GeneralPlayer::HandRating compPlayerRating;
	player.getHandRank(table, playerRating);
	compPlayer.getHandRank(table, compPlayerRating);
	bool playerWon = true;
	bool isSplit = false;

	if (playerRating.pokerHand == compPlayerRating.pokerHand) //combinations from strongest to weakest
	{
		switch (playerRating.pokerHand)
		{
		case GeneralPlayer::ROYAL_FLUSH:
			isSplit = true;
			break;
		case GeneralPlayer::STRAIGHT_FLUSH:
			if (playerRating.handRank1 < compPlayerRating.handRank1) // checks whose show down is in higher ranking
				playerWon = false;
			break;
		case GeneralPlayer::FOUR_OF_KIND:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
				playerWon = false;
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				if (playerRating.kickerRank < compPlayerRating.kickerRank)
					playerWon = false;
				else if (playerRating.kickerRank == compPlayerRating.kickerRank)
					isSplit = true;
			}
			break;
		case GeneralPlayer::FULL_HOUSE:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
			{
				playerWon = false;
			}
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				if (playerRating.handRank2 < compPlayerRating.handRank2)
					playerWon = false;
				else if (playerRating.handRank2 == compPlayerRating.handRank2)
					isSplit = true;
			}
			break;
		case GeneralPlayer::FLUSH:
			for (int i = 0; i < 5; ++i)
			{
				if (playerRating.kickerRank[i] < compPlayerRating.kickerRank[i])
				{
					playerWon = false;
					isSplit = false;
					break;
				}
				else if (playerRating.kickerRank[i] == compPlayerRating.kickerRank[i])
				{
					isSplit = true;
				}
				else
				{
					isSplit = false; // if player wins (playerWon default is true)
					break;
				}
			}
			break;
		case GeneralPlayer::STRAIGHT:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
			{
				playerWon = false;
			}
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				isSplit = true;
			}
			break;
		case GeneralPlayer::THREE_OF_KIND:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
			{
				playerWon = false;
			}
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				for (int i = 0; i < 2; ++i)
				{
					isSplit = true;
					if (playerRating.kickerRank[i] < compPlayerRating.kickerRank[i])
					{
						isSplit = false;
						playerWon = false;
						break;
					}

				}
			}
			break;
		case GeneralPlayer::TWO_PAIR:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
			{
				playerWon = false;
			}
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				if (playerRating.handRank2 < compPlayerRating.handRank2)
				{
					playerWon = false;
				}
				else if (playerRating.handRank2 == compPlayerRating.handRank2)
				{
					if (playerRating.kickerRank[0] < compPlayerRating.kickerRank[0])
					{
						playerWon = false;
					}
					else if (playerRating.kickerRank[0] == compPlayerRating.kickerRank[0])
						isSplit = true;
				}

			}
			break;
		case GeneralPlayer::ONE_PAIR:
			if (playerRating.handRank1 < compPlayerRating.handRank1)
			{
				playerWon = false;
			}
			else if (playerRating.handRank1 == compPlayerRating.handRank1)
			{
				for (int i = 0; i < 3; ++i)
				{
					isSplit = true;
					if (playerRating.kickerRank[i] < compPlayerRating.kickerRank[i])
					{
						isSplit = false;
						playerWon = false;
						break;
					}

				}
			}
			break;
		case GeneralPlayer::HIGH_CARD:

			for (int i = 0; i < 5; ++i)
			{
				isSplit = true;
				if (playerRating.kickerRank[i] < compPlayerRating.kickerRank[i])
				{
					isSplit = false;
					playerWon = false;
					break;
				}
			}
			break;
		default:
			break;
		}
		if (!isSplit)
		{
			if (playerWon)	player.win();
			else player.loose();
		}
		else cout << "It is a split!" << endl;
	}
	else if (playerRating.pokerHand > compPlayerRating.pokerHand)
	{
		player.win();
	}
	else
	{
		player.loose();
	}
		
}