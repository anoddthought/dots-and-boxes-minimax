#pragma once
#include <string>
#include <vector>
#include "Line.h"
using namespace std;

class Player
{
protected:
	string name;			//2 character name of player
	int total_score;		//total amount of games the player has won
	int game_score;			//score of the game being played currently
	int ai;					//type of ai, human = 0, minimax = 1

public:
	~Player();
	//functions handling game_score
	void resetGameScore() { game_score = 0; }
	void incrementGameScore() { game_score++; }
	int getGameScore() { return game_score; }

	//functions handling total_score
	void resetAll() { total_score = 0; game_score = 0; }		//resets both scores
	void incrementTotalScore() { total_score++; }				//increment player's total_score
	int getTotalScore() { return total_score; }

	//functions handling name
	void setName(string n) { name = n; }
	string getName() { return name; }

	//functions handling AI
	void setAI(int x) { ai = x; }
	int getAI() { return ai; }

	//function to determine the next move, modified in child classes for each type of player) {};

	//constructor no-arg
	Player() { game_score = 0; total_score = 0; }

	//copy constructor
	Player(const Player& p)
	{//copy all variables to this object
		name = p.name;
		total_score = p.total_score;
		game_score = p.game_score;
	}
	//overload = operator
	Player operator= (const Player& p)
	{
		//copy all variables to this object
		name = p.name;
		total_score = p.total_score;
		game_score = p.game_score;
	}
};