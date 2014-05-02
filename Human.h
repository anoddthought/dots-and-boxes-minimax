#pragma once
#include "Player.h"


class Human : public Player
{

public:
	virtual string getMove() override;
	Human();
	~Human();
};

