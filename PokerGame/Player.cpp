#include "stdafx.h"
#include "Player.h"


Player::Player(const string& name):
	GeneralPlayer(name)
{
}

Player::~Player()
{
}

void Player::win() const
{
	cout << m_name << " wins" << endl;
}
void Player::loose() const
{
	cout << m_name << " loose" << endl;
}

int Player::bidding()
{
	return 0; // soon to be
}