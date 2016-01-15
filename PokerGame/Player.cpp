#include "stdafx.h"
#include "Player.h"


Player::Player(const string& name):
	GeneralPlayer(name)
{
}
Player::Player(const Player& player)
{
	m_cards = player.m_cards;
	m_name = player.m_name;
}

Player::~Player()
{
}



int Player::bidding()
{
	return 0; // soon to be
}