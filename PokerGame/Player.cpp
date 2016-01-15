#include "stdafx.h"
#include "Player.h"


Player::Player(const string& name):
	GeneralPlayer(name)
{
	cout << "Player reg const called" << endl;
}
//Player::Player(const Player& player)
//{
//	cout << "Player copy const called" << endl;
//	m_cards.reserve(player.m_cards.size());
//	for (int i = 0; i < player.m_cards.size(); ++i)
//		m_cards[i] = player.m_cards[i];
//
//	m_name = player.m_name;
//}

Player::~Player()
{
}



int Player::bidding()
{
	return 0; // soon to be
}