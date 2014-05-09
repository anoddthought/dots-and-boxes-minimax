#pragma once
#include "Data.h"
#include <vector>
using namespace std;

class Minimax
{
	int maxPlayer, minPlayer;
public:
	Minimax();
	~Minimax();
	Line* mini_max(Data*,int);
	int max(Data*,int,int,int);
	int min(Data*,int,int,int);
};

