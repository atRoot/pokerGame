#pragma once
#include "GeneralPlayer.h"
class CompPlayer :
	public GeneralPlayer
{
public:
	CompPlayer(const string& name ="");
	//CompPlayer(const CompPlayer& compPlayer);
	virtual int bidding();
	~CompPlayer();
};

