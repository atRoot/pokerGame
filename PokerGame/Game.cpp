#include "stdafx.h"
#include "Game.h"


Game::Game(const vector<string>& names)
{
	const int NUMBER_OF_PLAYERS = 4;
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
		m_players.push_back(CompPlayer(compPlayerName));
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
	for (int i = 0; i <2 ; ++i)
	{
		vector<GeneralPlayer*>::iterator player = m_players.begin();
		for (; player != m_players.end(); ++player)
		{
			m_deck.deal(*(*player));
		}
		//m_deck.deal(m_player);
		//m_deck.deal(m_compPlayer);
	}
	m_compPlayer.flipCards();

	cout << m_compPlayer << endl;
	cout << m_player << endl;


	//cout << "Press enter to continue"<<endl;
	//cin.ignore();

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

	m_compPlayer.flipCards();
	cout <<'\n'<< m_compPlayer << endl;

	compareHands(m_player, m_compPlayer, m_table);

	m_player.clear();
	m_compPlayer.clear();
	m_table.clear();
	m_deck.reset();
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