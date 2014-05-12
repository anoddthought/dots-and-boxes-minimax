#pragma once
#include "Data.h"
#include <vector>
using namespace std;

struct minimaxmove{
	Line* move;
	int value;
};
class Minimax
{
	int maxPlayer, minPlayer;
public:
	Minimax();
	~Minimax();
	Line* mini_max(Data*,int);
	minimaxmove max(Data*,int,bool);
	minimaxmove min(Data*,int);
};

