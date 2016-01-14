#pragma once
#include "GeneralPlayer.h"
class Player :
	public GeneralPlayer
{
public:
	Player(const string& name ="");
	virtual ~Player();
	virtual int bidding();

};

