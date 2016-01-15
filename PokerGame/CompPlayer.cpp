#include "stdafx.h"
#include "CompPlayer.h"


CompPlayer::CompPlayer(const string& name) :GeneralPlayer(name)
{
}
//CompPlayer::CompPlayer(const CompPlayer& compPlayer)
//{
//	m_cards.reserve(compPlayer.m_cards.size());
//	for (int i = 0; i < compPlayer.m_cards.size(); ++i)
//		m_cards[i] = compPlayer.m_cards[i];
//
//	m_name = compPlayer.m_name;
//}
int CompPlayer::bidding()
{
	return 0; //yet to be implemented
}

CompPlayer::~CompPlayer()
{
}
