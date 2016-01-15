#pragma once
#include "GeneralPlayer.h"
class Player :
	public GeneralPlayer
{
public:
	Player(const string& name ="");
	//Player(const Player& player);
	virtual ~Player();
	virtual int bidding();

};

