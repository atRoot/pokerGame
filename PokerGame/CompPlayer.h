#pragma once
#include "GeneralPlayer.h"
class CompPlayer :
	public GeneralPlayer
{
public:
	CompPlayer(const string& name ="");
	virtual int bidding();
	~CompPlayer();
};

