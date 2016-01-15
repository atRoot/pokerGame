#include "stdafx.h"
#include "CompPlayer.h"


CompPlayer::CompPlayer(const string& name) :GeneralPlayer(name)
{
}
CompPlayer::CompPlayer(const CompPlayer& compPlayer)
{
	m_cards = compPlayer.m_cards;
	m_name = compPlayer.m_name;
}
int CompPlayer::bidding()
{
	return 0; //yet to be implemented
}

CompPlayer::~CompPlayer()
{
}
